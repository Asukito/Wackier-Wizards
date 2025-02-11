// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../../Components/HealthComponent.h"
#include "WWPlayerController.h"
#include "../../Spells/SpellBase.h"
#include "../../Spells/SpellData.h"
#include "../../Spells/SpellFactory.h"
#include "../../Components/EffectsComponent.h"

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

	_effectComponent = CreateDefaultSubobject<UEffectsComponent>(TEXT("Effects Component"));
	checkf(_effectComponent, TEXT("Player EffectsComponent failed to initialise"));

}

void APlayerCharacter::SetController(AWWPlayerController* controller)
{
	_playerController = controller;
}

bool APlayerCharacter::TakeDamage(int amount, FString source)
{
	_healthComponent->AdjustHealth(amount * -1);
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("%s: Taken %i damage from %s"), *GetName(), amount, *source));

	bool isDead = (_healthComponent->GetHealth() <= 0);

	if (isDead)
	{
		Kill();
	}

	return isDead;
}

void APlayerCharacter::Heal(int amount)
{
	_healthComponent->AdjustHealth(amount);
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, FString::Printf(TEXT("%s: Healed %i health"), *GetName(), amount));
}

void APlayerCharacter::AdjustMaxHealth(int amount)
{
	_healthComponent->AdjustMaxHealth(amount);
}

void APlayerCharacter::AdjustWalkSpeed(float percent)
{
	float absolute = _maxWalkSpeed * FMath::Abs(percent / 100);

	if (percent >= 0)
	{
		GetCharacterMovement()->MaxWalkSpeed += absolute;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed -= absolute;
	}
}

void APlayerCharacter::Kill()
{
	_healthComponent->SetHealth(0.0f);
	Respawn(true);
}

void APlayerCharacter::Respawn(bool isDead)
{
	_effectComponent->ClearEffects();

	if (isDead == true)
	{
		_healthComponent->SetHealth(_healthComponent->GetMaxHealth());
		SetActorLocation(_spawnLocation);
	}
	else
	{
		SetActorLocation(_lastValidPosition);
	}
}

void APlayerCharacter::AddEffect(UEffectData* effect)
{
	_effectComponent->CreateAndAddEffect(effect);
}

const int APlayerCharacter::GetHealth(bool getPercent) noexcept
{
	if (getPercent == true)
	{ 
		return _healthComponent->GetHealthPercent();
	}

	return _healthComponent->GetHealth();
}
const int APlayerCharacter::GetMaxHealth() noexcept
{
	return _healthComponent->GetMaxHealth();
}

bool APlayerCharacter::HasEffect(FString effectName)
{
	return _effectComponent->Contains(effectName);
}

const FVector APlayerCharacter::GetSeekLocation() const noexcept
{
	if (_seek == false)
	{
		return FVector::ZeroVector;
	}

	return GetActorLocation();
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

void APlayerCharacter::ToggleSeek()
{
	_seek = !_seek;
}


// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	_lastValidPosition = GetActorLocation();
	_spawnLocation = _lastValidPosition;

	_maxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_validUpdateTimer += DeltaTime;

	if (_validUpdateTimer >= 3.0f)
	{
		if (GetCharacterMovement()->IsFalling() == false)
		{
			_lastValidPosition = GetActorLocation();
			_validUpdateTimer = 0.0f;
		}
	}
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
IDamageable* APlayerCharacter::GetDamageableAccess()
{
	return Cast<IDamageable>(this);
}
IHealth* APlayerCharacter::GetHealthAccess()
{
	return Cast<IHealth>(this);
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
	return GetActorLocation() + (GetActorForwardVector() * 100) + FVector(0, 0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight() / 2);
}
#pragma endregion