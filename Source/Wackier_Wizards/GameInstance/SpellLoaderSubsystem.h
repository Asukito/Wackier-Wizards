// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SpellLoaderSubsystem.generated.h"

class USpellFactory;
class ISpell;
class ISpellCaster;
class USpellData;
class UTexture;
struct FSpellTableData;

UCLASS(Blueprintable)
class WACKIER_WIZARDS_API USpellLoaderSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void LoadDataTable();
	UFUNCTION(BlueprintCallable)
	USpellData* GetSpellData(int id);

	UFUNCTION(BlueprintCallable)
	TArray<int> GetSpellIDs();
	UFUNCTION(BlueprintCallable)
	UTexture* GetSpellIcon(int id);
	UFUNCTION(BlueprintCallable)
	bool GetSpellTableData(int id, FSpellTableData& OutData);

	ISpell* CreateSpell(USpellData* data, ISpellCaster* owner);

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
private:
	UPROPERTY()
	TObjectPtr<UDataTable> _spellDataTable;

	TMap<int, FSpellTableData*> _spellMap;

	UPROPERTY()
	TObjectPtr<USpellFactory> _spellFactory;
};
