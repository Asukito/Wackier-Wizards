// Fill out your copyright notice in the Description page of Project Settings.


#include "FalseFloorTrap.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AFalseFloorTrap::AFalseFloorTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	checkf(_staticMesh, TEXT("Portal Trap StaticMeshComponent failed to initialise"));
	_staticMesh->SetCollisionProfileName(FName("BlockAll"));
	_staticMesh->SetGenerateOverlapEvents(true);
	SetRootComponent(_staticMesh);

	_triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	checkf(_triggerBox, TEXT("False Floor TriggerBox failed to intitialise"));
	_triggerBox->bHiddenInGame = false;
	_triggerBox->SetVisibility(true);
	_triggerBox->SetCollisionProfileName(FName("Aura"));
	_triggerBox->SetGenerateOverlapEvents(true);
	_triggerBox->SetupAttachment(RootComponent);
}

void AFalseFloorTrap::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (_triggered == true || OtherActor == nullptr || Cast<ACharacter>(OtherActor) == nullptr)
	{
		return;
	}

	_staticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	_staticMesh->SetVisibility(false);
	_triggered = true;
}

// Called when the game starts or when spawned
void AFalseFloorTrap::BeginPlay()
{
	Super::BeginPlay();
	
	_triggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFalseFloorTrap::BeginOverlap);

	_resetTimer = 2.0f;
	_triggered = false;
}

// Called every frame
void AFalseFloorTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_triggered == false)
	{
		return;
	}

	_resetTimer -= DeltaTime;

	if (_triggered == true && _resetTimer <= 0)
	{
		_staticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		_staticMesh->SetVisibility(true);
		_resetTimer = 2.0f;
		_triggered = false;
	}
}

