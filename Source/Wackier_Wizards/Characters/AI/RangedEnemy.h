// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "RangedEnemy.generated.h"

class USpellCasterComponent;
class UGOAP_Agent;
class USpellBase;
class ISpell;

UCLASS()
class WACKIER_WIZARDS_API ARangedEnemy : public ABaseEnemy
{
	GENERATED_BODY()
	
public:
	ARangedEnemy();

	void CastSpell();
	ISpell* GetSpell();

	void BindDelegates() override;

	virtual const FVector GetCastStartLocation();
	virtual const FVector GetCastStartForward();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<USpellCasterComponent> spellCasterComponent;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UGOAP_Agent> _agent;
};
