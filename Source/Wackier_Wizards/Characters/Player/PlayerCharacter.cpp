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

void APlayerCharacter::SetController(AWWPlayerController* controller)
{
	playerController = controller;
}

void APlayerCharacter::Respawn(bool isDead)
{
	if (isDead == true)
	{
		ABaseCharacter::Respawn(isDead);
		return;
	}

	SetActorLocation(lastValidPosition);
}

void APlayerCharacter::CastSpell()
{
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

const FVector APlayerCharacter::GetSeekLocation() const noexcept
{
	if (seek == false)
	{
		return FVector::ZeroVector;
	}

	return GetActorLocation();
}

void APlayerCharacter::BindDelegates()
{
	ABaseCharacter::BindDelegates();

	spellCasterComponent->BindCastStartForward([this]() { return GetCastStartForward(); });
	spellCasterComponent->BindCastStartLocation([this]() { return GetCastStartLocation(); });
}

void APlayerCharacter::ToggleSeek()
{
	seek = !seek;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	ABaseCharacter::BeginPlay();

	lastValidPosition = GetActorLocation();
	spellCasterComponent->InitSpells();
}

// Called every frame
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
	return GetActorLocation() + (GetActorForwardVector()) + FVector(0, 0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight() / 2);
}
const FVector APlayerCharacter::GetCastStartForward()
{
	return camera->GetForwardVector();
}
#pragma endregion