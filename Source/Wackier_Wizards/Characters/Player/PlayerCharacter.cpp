// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "../../Components/HealthComponent.h"
#include "WWPlayerController.h"
#include "../../Spells/SpellBase.h"
#include "../../Spells/SpellData.h"
#include "../../Spells/SpellFactory.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
	bUseControllerRotationPitch = false;

	_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	checkf(_camera, TEXT("Player Camera failed to initialise"));
	_camera->SetupAttachment(RootComponent);
	_camera->bUsePawnControlRotation = true;

	_staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	checkf(_staticMesh, TEXT("Player StaticMesh failed to initialise"));
	_staticMesh->SetupAttachment(_camera);

	_healthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	checkf(_healthComponent, TEXT("Player HealthComponent failed to initialise"));
}

void APlayerCharacter::SetController(AWWPlayerController* controller)
{
	_playerController = controller;
}

void APlayerCharacter::TakeDamage(int amount, FString source)
{
	_healthComponent->AdjustHealth(amount * -1);
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("%s: Taken %i damage from %s"), *GetName(), amount, *source));
}

void APlayerCharacter::Heal(int amount)
{
	_healthComponent->AdjustHealth(amount);
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, FString::Printf(TEXT("%s: Healed %i health"), *GetName(), amount));
}

void APlayerCharacter::CastSpell()
{
	if (spell == nullptr)
	{
		return;
	}

	spell->CastSpell();
}

void APlayerCharacter::ChangeSpell(int slot)
{
	if (spellData.Num() == 0 || slot - 1 < 0 || slot > spellData.Num())
	{
		return;
	}

	USpellFactory* factory = NewObject<USpellFactory>();
	spell = factory->CreateSpell(spellData[slot - 1], this);
}


// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

#pragma region "Helpers"
UCameraComponent* APlayerCharacter::GetCamera() const noexcept
{
	return _camera;
}

float APlayerCharacter::GetHorizontalSensitivity() const noexcept
{
	return _horizontalSensitivity;
}

float APlayerCharacter::GetVerticalSensitivity() const noexcept
{
	return _verticalSensitivity;
}
AActor* APlayerCharacter::GetSpellOwner() noexcept
{
	return this;
}
const FVector APlayerCharacter::GetSpellOwnerLocation() noexcept
{
	return GetActorLocation();
}
const FVector APlayerCharacter::GetSpellOwnerForward() noexcept
{
	return _camera->GetForwardVector();
}
const FVector APlayerCharacter::GetCastStartLocation() noexcept
{
	return GetActorLocation() + FVector(0, 0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight() / 2);
}
#pragma endregion