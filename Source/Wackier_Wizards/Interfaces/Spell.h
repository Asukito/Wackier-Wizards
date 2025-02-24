// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Spell.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USpell : public UInterface
{
	GENERATED_BODY()
};

class USpellData;
class ISpellCaster;
class USpellBase;
class IEffectable;

class WACKIER_WIZARDS_API ISpell
{
	GENERATED_BODY()

//Interface that contains functions needed for all spells.
public:

	virtual void Init(USpellData* data, ISpellCaster* owner) {};
	virtual bool CastSpell() { return false; };

	virtual void Update(float deltaTime) {};
	virtual void ProcessHit(AActor* hit, FVector location, int damageAdjustment) {};

	virtual void SetOwnerSpell(ISpell* owner) {};

	virtual USpellBase* GetBaseSpell() { return nullptr; };
	virtual ISpell* GetDecorator() { return nullptr; };

	virtual const FString GetSpellName() { return TEXT(" "); };
	virtual const float GetSpellRange() { return 0.0f; }
	virtual USpellData* GetSpellData() { return nullptr; };
	virtual ISpellCaster* GetSpellOwner() { return nullptr; };
	virtual bool IsOnCooldown() { return false;};
	virtual int GetSpellDamage() { return 0; };

	virtual void FireLineTrace(AActor* owner, FVector start, FVector end, FVector& OutEnd) {};
	virtual void FireProjectile(FVector direction) {};
};
