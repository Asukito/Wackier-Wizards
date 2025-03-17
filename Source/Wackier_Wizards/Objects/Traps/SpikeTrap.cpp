// Fill out your copyright notice in the Description page of Project Settings.


#include "SpikeTrap.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "../../Interfaces/Damageable.h"

// Sets default values
ASpikeTrap::ASpikeTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_spikeMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Spike Mesh"));
	checkf(_spikeMesh, TEXT("Spike Trap SpikeMesh failed to intitialise"));
	_spikeMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetRootComponent(_spikeMesh);

	_triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	checkf(_triggerBox, TEXT("Spike Trap TriggerBox failed to intitialise"));
	_triggerBox->bHiddenInGame = false;
	_triggerBox->SetVisibility(true);
	_triggerBox->SetCollisionProfileName(FName("Aura"));
	_triggerBox->SetGenerateOverlapEvents(true);
	_triggerBox->SetupAttachment(RootComponent);
}

void ASpikeTrap::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr || _overlaps.Contains(OtherActor) == true)
	{
		return;
	}

	if (ACharacter* character = Cast<ACharacter>(OtherActor))
	{
		_overlaps.Add(character);
	}
}

void ASpikeTrap::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == nullptr || _overlaps.Contains(OtherActor) == false)
	{
		return;
	}

	if (ACharacter* character = Cast<ACharacter>(OtherActor))
	{
		_overlaps.Remove(character);
	}
}

// Called when the game starts or when spawned
void ASpikeTrap::BeginPlay()
{
	Super::BeginPlay();

	_triggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASpikeTrap::BeginOverlap);
	_triggerBox->OnComponentEndOverlap.AddDynamic(this, &ASpikeTrap::EndOverlap);

	_cooldownTimer = _triggerCooldown;
}

// Called every frame
void ASpikeTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_cooldownTimer -= DeltaTime;

	
	if (_cooldownTimer > 0 || _overlaps.Num() == 0)
	{
		return;
	}

	if (_animation != nullptr)
	{
		_spikeMesh->PlayAnimation(_animation, false);
	}

	int size = _overlaps.Num();

	for (TObjectPtr<ACharacter> character : _overlaps)
	{
		if (character == nullptr)
		{
			continue;
		}

		if (IDamageable* target = Cast<IDamageable>(character))
		{
			target->DealDamage(damage, FString("Spike Trap"));
		}

		if (_overlaps.Num() != size)
		{
			break;
		}
	}

	_cooldownTimer = _triggerCooldown;
}

