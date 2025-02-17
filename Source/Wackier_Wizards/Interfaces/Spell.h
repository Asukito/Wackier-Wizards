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

/**
 * 
 */
class WACKIER_WIZARDS_API ISpell
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void Init(class USpellData* data,  class ISpellCaster* owner) {};
	virtual bool CastSpell() { return false; };

	virtual void Update(float deltaTime) {};
	virtual void ProcessHit(AActor* hit, FVector location) {};

	virtual void SetOwnerSpell(ISpell* owner) {};
	virtual class USpellBase* GetBaseSpell() { return nullptr; };
	virtual ISpell* GetOwnerSpell() { return nullptr; };

	virtual const FString GetSpellName() { return TEXT(" "); };
	virtual const float GetSpellRange() { return 0.0f; }
	virtual USpellData* GetSpellData() { return nullptr; };
	virtual ISpellCaster* GetSpellOwner() { return nullptr; };
	virtual bool IsOnCooldown() { return false;};

	virtual void HandleEffects(class IEffectable* target) {};
	virtual void HandleInterfaceFunctions(AActor* actor) {};
};
