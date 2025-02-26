// Fill out your copyright notice in the Description page of Project Settings.


#include "FakeHealPotion.h"
#include "../../Characters/BaseCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AFakeHealPotion::AFakeHealPotion()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	checkf(_staticMesh, TEXT("Fake Heal Potion StaticMeshComponent failed to initialise"));
	_staticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetRootComponent(_staticMesh);

	_triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	checkf(_triggerBox, TEXT("Fake Heal Potion TriggerBox failed to intitialise"));
	_triggerBox->bHiddenInGame = false;
	_triggerBox->SetVisibility(true);
	_triggerBox->SetCollisionProfileName(FName("Aura"));
	_triggerBox->SetGenerateOverlapEvents(true);
	_triggerBox->SetupAttachment(RootComponent);
}

void AFakeHealPotion::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr)
	{
		return;
	}

	if (TObjectPtr<ABaseCharacter> character = Cast<ABaseCharacter>(OtherActor))
	{
		float random = FMath::RandRange(0, 100);

		if (random < 50)
		{
			character->GetDamageableAccess()->DealDamage(_damageAmount, "Random Potion");
		}
		else
		{
			character->GetHealthAccess()->Heal(_healAmount);
		}

		Destroy();
	}
}

// Called when the game starts or when spawned
void AFakeHealPotion::BeginPlay()
{
	Super::BeginPlay();

	_triggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFakeHealPotion::BeginOverlap);
}

// Called every frame
void AFakeHealPotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

