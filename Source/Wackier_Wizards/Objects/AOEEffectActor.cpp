// Fill out your copyright notice in the Description page of Project Settings.


#include "AOEEffectActor.h"
#include "Components/SphereComponent.h"
#include "../Interfaces/Effectable.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Wackier_Wizards/Definitions.h"

// Sets default values
AAOEEffectActor::AAOEEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	checkf(_collider, TEXT("AOE Actor Sphere Component failed to initialise"));
	_collider->SetCollisionProfileName(FName("Aura"));
}

void AAOEEffectActor::Init(UEffectData* data, float lifeTime, float aoeSize, float overlapDelay)
{
	_aoeSize = aoeSize;	

	_effect = data;
	_collider->bHiddenInGame = false;
	_collider->InitSphereRadius(_aoeSize);

	_lifeTime = lifeTime;

	DoAoe();

	if (_effect->type == EffectType::INSTANT)
	{
		Destroy();
		return;
	}

	_overlapDelay = overlapDelay;
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

// Called when the game starts or when spawned
void AAOEEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAOEEffectActor::DoAoe()
{
	TArray<TEnumAsByte<EObjectTypeQuery>> types;
	types.Add(UEngineTypes::ConvertToObjectType(ECC_DamageableObject));
	types.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	TArray<AActor*> targets;

	DrawDebugSphere(GetWorld(), GetActorLocation(), _aoeSize, 12, FColor::Red, false, _overlapDelay);
	if (UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetActorLocation(), _aoeSize, types, NULL, _ignore, targets))
	{
		for (TObjectPtr<AActor> actor : targets)
		{
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

	_overlapTimer += DeltaTime;
	if ( _overlapTimer < _overlapDelay)
	{
		return;
	}

	DoAoe();

	_overlapTimer = 0.0f;
}

