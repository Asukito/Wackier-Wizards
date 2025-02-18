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
	
public:
	void Init(USpellData* data, ISpellCaster* owner) override;
	virtual bool CastSpell();
	virtual void ProcessHit(AActor* hit, FVector location) override;
	void SetOwnerSpell(ISpell* owner) override;

	void Update(float deltaTime) override;

	virtual USpellBase* GetBaseSpell() override;

	const FString GetSpellName() override;
	const float GetSpellRange() override;
	USpellData* GetSpellData() override;
	ISpellCaster* GetSpellOwner() override;

	bool IsOnCooldown() override;

	void HandleEffects(IEffectable* target) override;
	void HandleInterfaceFunctions(AActor* actor) override;

	void SetProjectile(AProjectile* projectile);
	AProjectile* GetProjectile();
protected:
	UPROPERTY()
	TScriptInterface<ISpell> ownerSpell;

	UPROPERTY()
	TWeakObjectPtr<USpellData> spellData;
	UPROPERTY()
	TScriptInterface<ISpellCaster> spellOwner;

private:
	TObjectPtr<AProjectile> _projectile;

	float _cooldown;
	float _cooldownTimer;
};
