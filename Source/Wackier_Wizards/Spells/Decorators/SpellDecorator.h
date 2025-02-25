// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../../Interfaces/Spell.h"
#include "SpellDecorator.generated.h"

class USpellData;
class ISpellCaster;
class IEffectable;

UCLASS(Abstract)
class WACKIER_WIZARDS_API USpellDecorator : public UObject, public ISpell
{
	GENERATED_BODY()
	
//Abstract Decorator class that all decorators derive from. A reference to the BaseSpell object is stored within the lowest level decorator.
// 
//The lowest level decorator will always be one of the main spell types, currently:
//ProjectileSpellDecorator
//BeamSpellDecorator
//HitscanSpellDecorator
//SelfSpellDecorator
// 
//These will hold references to the SpellBase
public:	
	//---- DECORATOR CREATION ----
	//Handles member assignment when decorating this
	void Decorate(ISpell* decorate);
	//Sets the previous level of this decorator. This can be a decorator, or the SpellBase if this is the lowest level decorator.
	void SetOwnerSpell(ISpell* owner) override;

	//---- SPELL OVERRIDES ----
	virtual bool CastSpell() override;
	virtual void Update(float deltaTime) override;
	//Function called when a hit occurs
	virtual void ProcessHit(AActor* hit, FVector location, int damageAdjustment) override;

	//---- SPELL HELPERS ----
	virtual const FString GetSpellName() override;
	virtual const float GetSpellRange() override;
	USpellData* GetSpellData() override;
	ISpellCaster* GetSpellOwner() override;
	virtual bool IsOnCooldown() override;
	virtual int GetSpellDamage() override;

	//---- DECORATOR HELPERS ----
	//Recursive function that returns the SpellBase object that is being decorated
	virtual USpellBase* GetBaseSpell() override;
	//Recursive function that returns the highest level decorator of this spell
	virtual ISpell* GetDecorator() override;

	virtual void FireLineTrace(AActor* owner, FVector start, FVector end, FVector& OutEnd) override;
	virtual void FireProjectile(FVector direction) override;

protected:
	//Reference to previous level of spell. This can be a decorator, or the SpellBase if this is the lowest level decorator
	UPROPERTY()
	TScriptInterface<ISpell> spell;
	//Reference to next level of spell. This will always be another decorator
	UPROPERTY()
	TScriptInterface<ISpell> ownerSpell;

	// The SpellData contained within the SpellBase
	UPROPERTY()
	TObjectPtr<USpellData> spellData;
	// The caster of this spell
	UPROPERTY()
	TScriptInterface<ISpellCaster> spellOwner;
};
