// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "WWAIController.h"
#include "../Player/PlayerCharacter.h"
#include "../../Components/SeekerComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseEnemy::ABaseEnemy() : ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_seeker = CreateDefaultSubobject<USeekerComponent>(TEXT("Seeker Component"));
	checkf(_seeker, TEXT("Base Enemy SeekerComponent failed to initialise"));
}

void ABaseEnemy::SetSeekTarget(AActor* target)
{
	_seeker->SetSeekTarget(target);
}

void ABaseEnemy::ClearSeekTarget()
{
	_seeker->ClearSeekTarget();
}

void ABaseEnemy::SetDestination(FVector destination)
{
}

void ABaseEnemy::ClearDestination()
{
}

bool ABaseEnemy::HasPath()
{
	return _controller->HasPath();
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

