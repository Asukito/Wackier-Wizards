// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalTrap.h"
#include "NavigationSystem.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APortalTrap::APortalTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	checkf(_staticMesh, TEXT("Portal Trap StaticMeshComponent failed to initialise"));
	_staticMesh->SetCollisionProfileName(FName("Aura"));
	_staticMesh->SetGenerateOverlapEvents(true);
	SetRootComponent(_staticMesh);
}

void APortalTrap::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr || Cast<ACharacter>(OtherActor) == nullptr)
	{
		return;
	}

	FNavLocation location;
	UNavigationSystemV1::GetNavigationSystem(GetWorld())->GetRandomPoint(location);

	OtherActor->SetActorLocation(location.Location);
}

// Called when the game starts or when spawned
void APortalTrap::BeginPlay()
{
	Super::BeginPlay();

	_staticMesh->OnComponentBeginOverlap.AddDynamic(this, &APortalTrap::BeginOverlap);
}

// Called every frame
void APortalTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

