// Fill out your copyright notice in the Description page of Project Settings.


#include "AOEActor.h"
#include "Components/SphereComponent.h"
#include "../Interfaces/Effectable.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AAOEActor::AAOEActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	checkf(_collider, TEXT("AOE Actor Sphere Component failed to initialise"));
	_collider->SetCollisionProfileName(FName("OverlapAll"));

	Tags.Add(FName("Effect"));
}

void AAOEActor::Init(UEffectData* data)
{
	_effect = data;
	_collider->bHiddenInGame = false;
	_collider->InitSphereRadius(_effect->bonusRange);

	_lifeTime = _effect->duration;

	DoAoe();

	if (_effect->type == EffectType::INSTANT)
	{
		Destroy();
		return;
	}

	_overlapDelay = _effect->aoeInterval;
}

void AAOEActor::AddIgnoredActors(TArray<AActor*> actors)
{
	for (TObjectPtr<AActor> actor : actors)
	{
		_ignore.Add(actor);
	}
}

// Called when the game starts or when spawned
void AAOEActor::BeginPlay()
{
	Super::BeginPlay();

}

void AAOEActor::DoAoe()
{
	TArray<TEnumAsByte<EObjectTypeQuery>> types;
	types.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
	types.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	types.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	TArray<AActor*> targets;

	DrawDebugSphere(GetWorld(), GetActorLocation(), _effect->bonusRange, 12, FColor::Red, false, _effect->duration);
	if (UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetActorLocation(), _effect->bonusRange, types, NULL, _ignore, targets))
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
void AAOEActor::Tick(float DeltaTime)
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

