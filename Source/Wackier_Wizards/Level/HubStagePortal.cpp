// Fill out your copyright notice in the Description page of Project Settings.


#include "HubStagePortal.h"
#include "../Characters/Player/PlayerCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "../GameInstance/StageLoaderSubsystem.h"
// Sets default values
AHubStagePortal::AHubStagePortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	checkf(_staticMesh, TEXT("Hub Stage Portal StaticMeshComponent failed to initialise"));
	_staticMesh->SetCollisionProfileName(FName("Aura"));
	_staticMesh->SetGenerateOverlapEvents(true);
	SetRootComponent(_staticMesh);
}

void AHubStagePortal::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr || Cast<APlayerCharacter>(OtherActor) == nullptr)
	{
		return;
	}

	if (TObjectPtr<UStageLoaderSubsystem> stageLoader = GetGameInstance()->GetSubsystem<UStageLoaderSubsystem>())
	{
		stageLoader->LoadStage(_stage);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString::Printf(TEXT("STAGE LOADER NULL")));
	}
}

// Called when the game starts or when spawned
void AHubStagePortal::BeginPlay()
{
	Super::BeginPlay();
	
	_staticMesh->OnComponentBeginOverlap.AddDynamic(this, &AHubStagePortal::BeginOverlap);
}

// Called every frame
void AHubStagePortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

