// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeNPC.h"
#include "WWAIController.h"
#include "../Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"
#include "../../Components/EffectsComponent.h"
#include "../../Components/HealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMeleeNPC::AMeleeNPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	_healthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	checkf(_healthComponent, TEXT("Player HealthComponent failed to initialise"));

	_effectComponent = CreateDefaultSubobject<UEffectsComponent>(TEXT("Effects Component"));
	checkf(_effectComponent, TEXT("Player EffectsComponent failed to initialise"));
}

void AMeleeNPC::AddEffect(UEffectData* effect)
{
	_effectComponent->CreateAndAddEffect(effect);
}

IDamageable* AMeleeNPC::GetDamageableAccess()
{
	return Cast<IDamageable>(this);
}

IHealth* AMeleeNPC::GetHealthAccess()
{
	return Cast<IHealth>(this);
}

bool AMeleeNPC::HasEffect(FString effectName)
{
	return _effectComponent->Contains(effectName);;
}

bool AMeleeNPC::TakeDamage(int amount, FString source)
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

void AMeleeNPC::Kill()
{
	Respawn(true);
}

void AMeleeNPC::Heal(int amount)
{
	_healthComponent->AdjustHealth(amount);
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, FString::Printf(TEXT("%s: Healed %i health"), *GetName(), amount));
}

void AMeleeNPC::AdjustMaxHealth(int amount)
{
	_healthComponent->AdjustMaxHealth(amount);
}

const int AMeleeNPC::GetHealth(bool getPercent) noexcept
{
	if (getPercent == true)
	{
		return _healthComponent->GetHealthPercent();
	}

	return _healthComponent->GetHealth();
}

const int AMeleeNPC::GetMaxHealth() noexcept
{
	return _healthComponent->GetMaxHealth();
}

void AMeleeNPC::Respawn(bool isDead)
{
	_effectComponent->ClearEffects();
	SetActorLocation(_spawnPoint);
	_healthComponent->SetHealth(_healthComponent->GetMaxHealth());
}

void AMeleeNPC::AdjustWalkSpeed(float percent)
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

// Called when the game starts or when spawned
void AMeleeNPC::BeginPlay()
{
	Super::BeginPlay();
	
	_controller = Cast<AWWAIController>(GetController());
	_player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	_spawnPoint = GetActorLocation();
	_maxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

void AMeleeNPC::Attack(IDamageable* target)
{
	if (_timer <= _meleeDelay)
	{
		return;
	}

	target->TakeDamage(_meleeDamage, "Melee NPC");
	_timer = 0.0f;
}

// Called every frame
void AMeleeNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_player == nullptr)
	{
		return;
	}

	_timer += DeltaTime;

	const FVector destination = _player->GetSeekLocation();

	if (destination != FVector::ZeroVector)
	{
		_controller->SetDestination(destination);

		const FVector distance = destination - GetActorLocation();

		if (distance.Length() < _meleeRange)
		{
			Attack(Cast<IDamageable>(_player));
		}
	}
	else
	{
		_controller->ClearDestination();
	}
}

