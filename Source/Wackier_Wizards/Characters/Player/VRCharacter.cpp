// Fill out your copyright notice in the Description page of Project Settings.


#include "VRCharacter.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "EnhancedPlayerInput.h"
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
AVRCharacter::AVRCharacter()
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

// Called when the game starts or when spawned
void AVRCharacter::BeginPlay()
{
	Super::BeginPlay();

	_lastValidPosition = GetActorLocation();
	
}

// Called every frame
void AVRCharacter::Tick(float DeltaTime)
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
void AVRCharacter::SetController(AWWPlayerController* controller)
{
	_playerController = controller;
}

void AVRCharacter::TakeDamage(int amount, FString source)
{
	_healthComponent->AdjustHealth(amount * -1);
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("%s: Taken %i damage from %s"), *GetName(), amount, *source));
}

void AVRCharacter::Heal(int amount)
{
	_healthComponent->AdjustHealth(amount);
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, FString::Printf(TEXT("%s: Healed %i health"), *GetName(), amount));
}

void AVRCharacter::AdjustMaxHealth(int amount)
{
	_healthComponent->AdjustMaxHealth(amount);
}

void AVRCharacter::Kill()
{
	_healthComponent->SetHealth(0.0f);
}

void AVRCharacter::Respawn()
{
	SetActorLocation(_lastValidPosition);
}

void AVRCharacter::AddEffect(UEffectData* effect)
{
	_effectComponent->CreateAndAddEffect(effect);
}

const int AVRCharacter::GetHealth(bool getPercent) noexcept
{
	if (getPercent == true)
	{
		return _healthComponent->GetHealthPercent();
	}

	return _healthComponent->GetHealth();
}
const int AVRCharacter::GetMaxHealth() noexcept
{
	return _healthComponent->GetMaxHealth();
}

bool AVRCharacter::HasEffect(FString effectName)
{
	return _effectComponent->Contains(effectName);
}
void AVRCharacter::CastSpell()
{
	if (spell == nullptr)
	{
		return;
	}

	spell->CastSpell();
	//log the location of the right hand
	UE_LOG(LogTemp, Warning, TEXT("Right Hand Location: %s"), *rightHandLocation.ToString());
}

void AVRCharacter::ChangeSpell(int slot)
{
	if (spellData.Num() == 0 || slot - 1 < 0 || slot > spellData.Num())
	{
		return;
	}

	USpellFactory* factory = NewObject<USpellFactory>();
	spell = factory->CreateSpell(spellData[slot - 1], this);
}


// Called to bind functionality to input
void AVRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Get the player controller
	APlayerController* PC = Cast<APlayerController>(GetController());

	//Get the local player subsystem
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());

	//Clear out the existing mappings, and add our mapping
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMappingContext, 0);

	//Get the Enhanced Input Component
	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	// Bind the actions
	PEI->BindAction(inputMove, ETriggerEvent::Triggered, this, &AVRCharacter::MovePlayer);
	PEI->BindAction(inputShootSpell, ETriggerEvent::Triggered, this, &AVRCharacter::ShootSpell);
	PEI->BindAction(inputChangeSpell, ETriggerEvent::Triggered, this, &AVRCharacter::ChangeSpell);
}

void AVRCharacter::ShootSpell()
{
	//log that the player is shooting a spell
	UE_LOG(LogTemp, Warning, TEXT("Player is shooting a spell"));
}

void AVRCharacter::ChangeSpell()
{//log that the player is changing the spell
	UE_LOG(LogTemp, Warning, TEXT("Player is changing the spell"));
}

void AVRCharacter::MovePlayer(const FInputActionValue& Value)
{
	//log the value of the input action value
	
	UE_LOG(LogTemp, Warning, TEXT("Value: %s"), *Value.ToString());
	//checks if the player controller is valid
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		//gets the forward vector of the player controller
		FVector ForwardVector = PC->GetControlRotation().Vector();
		//gets the right vector of the player controller
		FVector RightVector = ForwardVector.RotateAngleAxis(90, FVector(0, 0, 1));
		//creates a movement vector
		FVector MovementVector = ForwardVector * Value.Get<FVector>().Y + RightVector * Value.Get<FVector>().X;
		//moves the player character
		AddMovementInput(MovementVector, 1);
		//prints the movement vector
		UE_LOG(LogTemp, Warning, TEXT("Movement Vector: %s"), *MovementVector.ToString());
	}

}
#pragma region "Helpers"
UCameraComponent* AVRCharacter::GetCamera() const noexcept
{
	return _camera;
}

float AVRCharacter::GetHorizontalSensitivity() const noexcept
{
	return _horizontalSensitivity;
}

float AVRCharacter::GetVerticalSensitivity() const noexcept
{
	return _verticalSensitivity;
}
IDamageable* AVRCharacter::GetDamageableAccess()
{
	return Cast<IDamageable>(this);
}
IHealth* AVRCharacter::GetHealthAccess()
{
	return Cast<IHealth>(this);
}
AActor* AVRCharacter::GetSpellOwner() noexcept
{
	return this;
}
const FVector AVRCharacter::GetSpellOwnerLocation() noexcept
{
	return GetActorLocation();
}
const FVector AVRCharacter::GetSpellOwnerForward() noexcept
{
	return _camera->GetForwardVector();
}
const FVector AVRCharacter::GetCastStartLocation() noexcept
{
	return rightHandLocation;
}

const FVector AVRCharacter::GetCastStartForward() noexcept
{
	return rightHandLocation;
}

#pragma endregion

