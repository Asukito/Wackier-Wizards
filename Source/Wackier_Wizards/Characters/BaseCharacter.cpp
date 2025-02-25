// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	healthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	checkf(healthComponent, TEXT("Player HealthComponent failed to initialise"));

	effectComponent = CreateDefaultSubobject<UEffectsComponent>(TEXT("Effects Component"));
	checkf(effectComponent, TEXT("Player EffectsComponent failed to initialise"));
}
// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	spawnLocation = GetActorLocation();
	maxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	canAttack = true;

	BindDelegates();
}

void ABaseCharacter::BindDelegates()
{
	//Any BeginPlay delegate binding goes here
}

#pragma region "IEffectable"
IDamageable* ABaseCharacter::GetDamageableAccess()
{
	return Cast<IDamageable>(this);
}
IHealth* ABaseCharacter::GetHealthAccess()
{
	return Cast<IHealth>(this);;
}

void ABaseCharacter::AddEffect(UEffectData* effect)
{
	effectComponent->CreateAndAddEffect(effect);
}
bool ABaseCharacter::HasEffect(FString effectName)
{
	return effectComponent->Contains(effectName);
}

UAuraEffect* ABaseCharacter::GetAura()
{
	return effectComponent->GetAura();
}

void ABaseCharacter::SetCanAct(bool val)
{
	//Disable movement
	canAttack = val;
}

bool ABaseCharacter::HasMovementComponent()
{
	return true;
}
void ABaseCharacter::AdjustWalkSpeed(float percent)
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
#pragma endregion

#pragma region "IDamageable"
bool ABaseCharacter::TakeDamage(int amount, FString source)
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
void ABaseCharacter::Kill()
{
	effectComponent->ClearEffects();
	Respawn(true);
}
#pragma endregion

#pragma region "IHealth"
void ABaseCharacter::Heal(int amount)
{
	healthComponent->AdjustHealth(amount);
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, FString::Printf(TEXT("%s: Healed %i health"), *GetName(), amount));
}
void ABaseCharacter::AdjustMaxHealth(int amount)
{
	healthComponent->AdjustMaxHealth(amount);
}
//Returns health. If getPercent is true, returns health percent based on max health.
const int ABaseCharacter::GetHealth(bool getPercent) noexcept
{
	if (getPercent == true)
	{
		return healthComponent->GetHealthPercent();
	}

	return healthComponent->GetHealth();
}

const int ABaseCharacter::GetBaseHealth() noexcept
{
	return healthComponent->GetBaseHealth();
}

const int ABaseCharacter::GetMaxHealth() noexcept
{
	return healthComponent->GetMaxHealth();
}
void ABaseCharacter::Respawn(bool isDead)
{
	if (isDead == true)
	{
		healthComponent->SetHealth(healthComponent->GetMaxHealth());
		SetActorLocation(spawnLocation);
	}
}
#pragma endregion







