// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "WWAIController.h"
#include "../Player/PlayerCharacter.h"
#include "../../Components/SeekerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ABaseEnemy::ABaseEnemy() : ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_seeker = CreateDefaultSubobject<USeekerComponent>(TEXT("Seeker Component"));
	checkf(_seeker, TEXT("Base Enemy SeekerComponent failed to initialise"));

	SetRootComponent(GetCapsuleComponent());

	GetMesh()->SetCollisionProfileName(FName("NoCollision"));
	GetMesh()->SetupAttachment(GetRootComponent());

	_sightCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Sight Collider"));
	checkf(_sightCollider, TEXT("BaseEnemy SightCollider failed to initialise"));
	_sightCollider->SetCollisionProfileName(FName("EnemyTrace"));
	_sightCollider->SetupAttachment(GetRootComponent());
	_sightCollider->bHiddenInGame = false;
}

void ABaseEnemy::SetSeekTarget(AActor* target)
{
	SetFocus(target);
	_seeker->SetSeekTarget(target);
}

void ABaseEnemy::ClearSeekTarget()
{
	_seeker->ClearSeekTarget();
	ClearFocus();
}

void ABaseEnemy::SetDestination(FVector destination)
{
	_controller->SetDestination(destination);
}

void ABaseEnemy::ClearDestination()
{
}

void ABaseEnemy::SetFocus(AActor* target)
{
	_controller->SetFocus(target);
}

void ABaseEnemy::ClearFocus()
{
	_controller->ClearFocus(EAIFocusPriority::Gameplay);
}

bool ABaseEnemy::HasPath()
{
	return _controller->HasPath();
}

const FVector ABaseEnemy::GetCurrentDestination()
{
	return _controller->GetCurrentDestination();
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	ABaseCharacter::BeginPlay();

	_controller = Cast<AWWAIController>(GetController());
	player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	_seeker->SetController(_controller);
	_seeker->SetIsActive(true);
}
// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

