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

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	checkf(camera, TEXT("Player Camera failed to initialise"));
	camera->SetupAttachment(RootComponent);
	camera->bUsePawnControlRotation = true;

	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	checkf(staticMesh, TEXT("Player StaticMesh failed to initialise"));
	staticMesh->SetupAttachment(camera);

	healthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	checkf(healthComponent, TEXT("Player HealthComponent failed to initialise"));

	effectComponent = CreateDefaultSubobject<UEffectsComponent>(TEXT("Effects Component"));
	checkf(effectComponent, TEXT("Player EffectsComponent failed to initialise"));

}

void APlayerCharacter::SetController(AWWPlayerController* controller)
{
	playerController = controller;
}

bool APlayerCharacter::TakeDamage(int amount, FString source)
{
	healthComponent->AdjustHealth(amount * -1);
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("%s: Taken %i damage from %s"), *GetName(), amount, *source));

	bool isDead = (healthComponent->GetHealth() <= 0);

	if (isDead)
	{
		Kill();
	}

	return isDead;
}

void APlayerCharacter::Heal(int amount)
{
	healthComponent->AdjustHealth(amount);
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, FString::Printf(TEXT("%s: Healed %i health"), *GetName(), amount));
}

void APlayerCharacter::AdjustMaxHealth(int amount)
{
	healthComponent->AdjustMaxHealth(amount);
}

void APlayerCharacter::AdjustWalkSpeed(float percent)
{
	float absolute = maxWalkSpeed * FMath::Abs(percent / 100);

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
	healthComponent->SetHealth(0.0f);
	Respawn(true);
}

void APlayerCharacter::Respawn(bool isDead)
{
	effectComponent->ClearEffects();

	if (isDead == true)
	{
		healthComponent->SetHealth(healthComponent->GetMaxHealth());
		SetActorLocation(spawnLocation);
	}
	else
	{
		SetActorLocation(lastValidPosition);
	}
}

void APlayerCharacter::AddEffect(UEffectData* effect)
{
	effectComponent->CreateAndAddEffect(effect);
}

const int APlayerCharacter::GetHealth(bool getPercent) noexcept
{
	if (getPercent == true)
	{ 
		return healthComponent->GetHealthPercent();
	}

	return healthComponent->GetHealth();
}
const int APlayerCharacter::GetMaxHealth() noexcept
{
	return healthComponent->GetMaxHealth();
}

bool APlayerCharacter::HasEffect(FString effectName)
{
	return effectComponent->Contains(effectName);
}

const FVector APlayerCharacter::GetSeekLocation() const noexcept
{
	if (seek == false)
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
	seek = !seek;
}

void APlayerCharacter::CycleSpell()
{
	_currentSpellIndex += 1;

	if (_currentSpellIndex > spellData.Num())
	{
		_currentSpellIndex = 1;
	}

	ChangeSpell(_currentSpellIndex);
}


// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	lastValidPosition = GetActorLocation();
	spawnLocation = lastValidPosition;

	maxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

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
	return camera->GetForwardVector();
}
const FVector APlayerCharacter::GetCastStartLocation() noexcept
{
	return GetActorLocation() + (GetActorForwardVector() * 100) + FVector(0, 0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight() / 2);
}
const FVector APlayerCharacter::GetCastStartForward() noexcept
{
	return GetActorForwardVector();
}
#pragma endregion