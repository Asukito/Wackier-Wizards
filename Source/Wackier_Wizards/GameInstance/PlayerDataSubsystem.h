// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PlayerDataSubsystem.generated.h"

class USpellData;

UCLASS(Blueprintable)
class WACKIER_WIZARDS_API UPlayerDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetSpells(TArray<int> spellIDs);
	UFUNCTION(BlueprintCallable)
	TArray<int> GetSavedSpellIDs();

	TArray<USpellData*> GetSpellsAsData();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
private:
	TArray<int> _spells;
};
