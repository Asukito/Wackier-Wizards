// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Interfaces/Spell.h"
#include "SpellBase.generated.h"

class USpellData;
class ISpellCaster;
class IEffectable;
class AProjectile;

UCLASS()
class WACKIER_WIZARDS_API USpellBase : public UObject, public ISpell
{
	GENERATED_BODY()
	
//The base Spell object. This is the object that is decorated by SpellDecorators.
public:
	//Initalises the spell member variables
	void Init(USpellData* data, ISpellCaster* owner) override;

	//---- SPELL FUNCTIONS ----
	virtual bool CastSpell();
	void Update(float deltaTime) override;
	//Function called when a hit occurs
	virtual void ProcessHit(AActor* hit, FVector location) override;

	//---- DECORATOR HELPERS ----
	//Sets a reference to the lowest level decorator applied to this spell.
	void SetOwnerSpell(ISpell* owner) override;
	//Returns this. The end of the recursive function used by Decorators.
	virtual USpellBase* GetBaseSpell() override;

	//---- HELPERS ----
	const FString GetSpellName() override;
	const float GetSpellRange() override;
	USpellData* GetSpellData() override;
	ISpellCaster* GetSpellOwner() override;
	bool IsOnCooldown() override;

	//---- POST-HIT FUNCTIONS ----
	//Handles the placement of effects on the target
	void HandleEffects(IEffectable* target) override;
	//Handles any relevant interface functions attached to the hit actor. This includes IDamageable, IHealth and IEffectable
	void HandleInterfaceFunctions(AActor* actor) override;

	//--- PROJECTILE FUNCTIONS ----
	//Sets a reference to a projectile created by this spell if necessary. Decorators can access this projectile, if needed, to add logic to the CastSpell function (such as initialising a Trail effect).
	void SetProjectile(AProjectile* projectile);
	AProjectile* GetProjectile();
protected:
	//A reference to the lowest level Decorator applied to this.
	UPROPERTY()
	TScriptInterface<ISpell> ownerSpell;
	//The data that contains the parameters/stats for this.
	UPROPERTY()
	TWeakObjectPtr<USpellData> spellData;
	//SpellCaster that owns this.
	UPROPERTY()
	TScriptInterface<ISpellCaster> spellOwner;

private:
	TObjectPtr<AProjectile> _projectile;

	//Spell cooldown + timer
	float _cooldown;
	float _cooldownTimer;
};
