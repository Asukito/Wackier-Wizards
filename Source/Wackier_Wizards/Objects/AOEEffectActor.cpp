// Fill out your copyright notice in the Description page of Project Settings.


#include "AOEEffectActor.h"
#include "Components/SphereComponent.h"
#include "../Interfaces/Effectable.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Wackier_Wizards/Definitions.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AAOEEffectActor::AAOEEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	checkf(_collider, TEXT("AOE Actor Sphere Component failed to initialise"));
	_collider->SetCollisionProfileName(FName("Aura"));
	_collider->bHiddenInGame = false;
	_collider->SetVisibility(true);
}

void AAOEEffectActor::Init(UEffectData* data, float lifeTime, float aoeSize, bool addPullEffect)
{
	_aoeSize = aoeSize;	
	_pullActors = addPullEffect;

	_effect = data;

	_collider->SetSphereRadius(_aoeSize);

	_lifeTime = lifeTime;

	Populate();

	if (_effect != nullptr && _effect->type == EffectType::INSTANT)
	{
		ProcessEffects();
		Destroy();
		return;
	}

	_collider->OnComponentBeginOverlap.AddDynamic(this, &AAOEEffectActor::BeginOverlap);
	_collider->OnComponentEndOverlap.AddDynamic(this, &AAOEEffectActor::EndOverlap);
}

void AAOEEffectActor::AddIgnoredActor(AActor* actor)
{
	if (_ignore.Contains(actor) == true)
	{
		return;
	}

	_ignore.Add(actor);
}

void AAOEEffectActor::AddIgnoredActors(TArray<AActor*> actors)
{
	for (TObjectPtr<AActor> actor : actors)
	{
		_ignore.Add(actor);
	}
}

void AAOEEffectActor::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (_ignore.Contains(OtherActor))
	{
		return;
	}

	if (_overlaps.Contains(OtherActor) == false)
	{
		_overlaps.Add(OtherActor);
	}
}

void AAOEEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (_ignore.Contains(OtherActor))
	{
		return;
	}

	if (_overlaps.Contains(OtherActor) == true)
	{
		_overlaps.Remove(OtherActor);
	}
}

// Called when the game starts or when spawned
void AAOEEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAOEEffectActor::Populate()
{
	TArray<TEnumAsByte<EObjectTypeQuery>> types;
	types.Add(UEngineTypes::ConvertToObjectType(ECC_DamageableObject));
	types.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	TArray<AActor*> targets;

	if (UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetActorLocation(), _aoeSize, types, NULL, _ignore, targets))
	{
		for (TObjectPtr<AActor> actor : targets)
		{
			_overlaps.Add(actor);
		}
	}
}

void AAOEEffectActor::ProcessEffects()
{
	for (TObjectPtr<AActor> actor : _overlaps)
	{
		if (_pullActors == true)
		{
			TArray<UCharacterMovementComponent*> components;
			actor->GetComponents<UCharacterMovementComponent>(components);

			if (components.Num() != 0)
			{
				FVector direction = actor->GetActorLocation() - GetActorLocation();
				direction.Normalize();

				components[0]->Launch(-direction * 500);
			}
		}

		if (_effect == nullptr)
		{
			continue;
		}

		if (IEffectable* target = Cast<IEffectable>(actor))
		{
			if (target->HasEffect(_effect->name))
			{
				continue;
			}

			target->AddEffect(_effect);
		}
	}
}

// Called every frame
void AAOEEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_lifeTimer += DeltaTime;

	if (_lifeTimer >= _lifeTime)
	{
		Destroy();
	}

	if (_overlaps.Num() == 0)
	{
		return;
	}

	ProcessEffects();
}

