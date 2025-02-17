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
	
public:	
	void Decorate(ISpell* decorate);
	void SetOwnerSpell(ISpell* owner) override;
	virtual bool CastSpell() override;
	virtual void Update(float deltaTime) override;
	virtual void ProcessHit(AActor* hit, FVector location) override;

	virtual const FString GetSpellName() override;
	virtual const float GetSpellRange() override;
	USpellData* GetSpellData() override;
	ISpellCaster* GetSpellOwner() override;
	virtual USpellBase* GetBaseSpell() override;
	virtual ISpell* GetDecorator() override;
	virtual bool IsOnCooldown() override;

	void HandleEffects(IEffectable* target) override;
	void HandleInterfaceFunctions(AActor* actor) override;
protected:
	UPROPERTY()
	TScriptInterface<ISpell> ownerSpell;

	UPROPERTY()
	TScriptInterface<ISpell> spell;
	UPROPERTY()
	TObjectPtr<USpellData> spellData;
	UPROPERTY()
	TScriptInterface<ISpellCaster> spellOwner;

	UPROPERTY()
	TObjectPtr<AActor> spellHit;
	FVector spellHitLocation;
};
