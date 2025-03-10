// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "WWPlayerController.h"
#include "../../Components/SpellCasterComponent.h"
#include "GenericPlatform/GenericPlatformMisc.h"

// Sets default values
APlayerCharacter::APlayerCharacter() : ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
	bUseControllerRotationPitch = false;

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	checkf(camera, TEXT("Player Camera failed to initialise"));
	camera->SetupAttachment(RootComponent);
	camera->bUsePawnControlRotation = true;

	spellCasterComponent = CreateDefaultSubobject<USpellCasterComponent>(TEXT("SpellCaster Component"));
	checkf(spellCasterComponent, TEXT("Player SpellCasterComponent failed to initialise"));
}

#pragma region "IHealth"
//Respawns at the spawnpoint if the player is dead. Spawns at the last valid position if not.
void APlayerCharacter::Respawn(bool isDead)
{
	if (isDead == true)
	{
		ABaseCharacter::Respawn(isDead);
		return;
	}

	SetActorLocation(lastValidPosition);
}
#pragma endregion

#pragma region "Spell Casting"
void APlayerCharacter::CastSpell()
{
	if (canAttack == false)
	{
		return;
	}

	spellCasterComponent->CastSpell();
}

void APlayerCharacter::ChangeSpell(int slot)
{
	spellCasterComponent->ChangeSpell(slot);
}

void APlayerCharacter::CycleSpell()
{
	spellCasterComponent->CycleSpell();
}
void APlayerCharacter::InitSpells()
{
	spellCasterComponent->InitSpells();
}
#pragma endregion

void APlayerCharacter::BindDelegates()
{
	ABaseCharacter::BindDelegates();

	spellCasterComponent->BindCastStartForward([this]() { return GetCastStartForward(); });
	spellCasterComponent->BindCastStartLocation([this]() { return GetCastStartLocation(); });
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	ABaseCharacter::BeginPlay();

	lastValidPosition = GetActorLocation();
	//spellCasterComponent->InitSpells();
}

// Called every frame
//Updates the character's last valid location every 3 seconds. This is used for respawning if the player falls from the map.
void APlayerCharacter::Tick(float DeltaTime)
{
	ABaseCharacter::Tick(DeltaTime);

	validUpdateTimer += DeltaTime;

	if (validUpdateTimer >= 3.0f)
	{
		if (GetCharacterMovement()->IsFalling() == false)
		{
			lastValidPosition = GetActorLocation();
			validUpdateTimer = 0.0f;
		}
	}
}

#pragma region "Helpers"
void APlayerCharacter::SetController(AWWPlayerController* controller)
{
	playerController = controller;
}
UCameraComponent* APlayerCharacter::GetCamera() const noexcept
{
	return camera;
}
float APlayerCharacter::GetHorizontalSensitivity() const noexcept
{
	return horizontalSensitivity;
}
float APlayerCharacter::GetVerticalSensitivity() const noexcept
{
	return verticalSensitivity;
}
const FVector APlayerCharacter::GetCastStartLocation()
{
	//prints to output log the cast start location
	FVector start = GetActorLocation() + (camera->GetForwardVector() * 50) + FVector(0, 0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight() / 2);
	UE_LOG(LogTemp, Warning, TEXT("Start: %s"), *start.ToString());
	return GetActorLocation() + (GetCamera()->GetForwardVector() * 50) + FVector(0, 0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight() / 2);
}
const FVector APlayerCharacter::GetCastStartForward()
{
	return camera->GetForwardVector();
}
#pragma endregion

#pragma region "Test"
void APlayerCharacter::ToggleSeek()
{
	seek = !seek;
}
//Returns the actor location if seeking is active. Returns a zero vector if not.
const FVector APlayerCharacter::GetSeekLocation() const noexcept
{
	if (seek == false)
	{
		return FVector::ZeroVector;
	}

	return GetActorLocation();
}
#pragma endregion