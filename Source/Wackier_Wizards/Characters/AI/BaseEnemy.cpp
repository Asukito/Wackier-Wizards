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

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	ABaseCharacter::BeginPlay();

	_controller = Cast<AWWAIController>(GetController());
	player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	_seeker->SetController(_controller);
	_seeker->SetSeekTarget(player.Get());
	_seeker->SetIsActive(true);
}
// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (player.IsValid() == false)
	{
		return;
	}
}

