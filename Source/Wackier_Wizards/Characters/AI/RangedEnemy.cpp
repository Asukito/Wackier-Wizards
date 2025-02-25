// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedEnemy.h"
#include "../../Components/SpellCasterComponent.h"
#include "Components/CapsuleComponent.h"
#include "GOAP/GOAP_Agent.h"
#include "../Player/PlayerCharacter.h"

ARangedEnemy::ARangedEnemy()
{
	spellCasterComponent = CreateDefaultSubobject<USpellCasterComponent>(TEXT("SpellCaster Component"));
	checkf(spellCasterComponent, TEXT("Player SpellCasterComponent failed to initialise"));

	_agent = CreateDefaultSubobject<UGOAP_Agent>(TEXT("GOAP Agent"));
	checkf(_agent, TEXT("RangedEnemy GOAP_AgentComponent failed to initialise"));
}

void ARangedEnemy::CastSpell()
{
	if (canAttack == false)
	{
		return;
	}

	spellCasterComponent->CastSpell();
}

ISpell* ARangedEnemy::GetSpell()
{
	return spellCasterComponent->GetActiveSpell();
}

void ARangedEnemy::BindDelegates()
{
	ABaseEnemy::BindDelegates();

	spellCasterComponent->BindCastStartForward([this]() { return GetCastStartForward(); });
	spellCasterComponent->BindCastStartLocation([this]() { return GetCastStartLocation(); });
}

const FVector ARangedEnemy::GetCastStartLocation()
{
	return GetActorLocation() + (GetActorForwardVector()) + FVector(0, 0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight() / 2);
}

const FVector ARangedEnemy::GetCastStartForward()
{
	return GetActorForwardVector();
}

void ARangedEnemy::BeginPlay()
{
	ABaseEnemy::BeginPlay();

	spellCasterComponent->InitSpells();

	if (player == nullptr)
	{
		return;
	}

	_agent->Init();
	_agent->SetPlayer(player);
}
