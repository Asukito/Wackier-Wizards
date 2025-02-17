// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Interfaces/SpellCaster.h"
#include "SpellCasterComponent.generated.h"

class USpellBase;
class USpellData;
class ISpell;

DECLARE_DELEGATE_RetVal(const FVector, FGetCastStart);
DECLARE_DELEGATE_RetVal(const FVector, FGetCastForward);

UCLASS()
class WACKIER_WIZARDS_API USpellCasterComponent : public UActorComponent, public ISpellCaster
{
	GENERATED_BODY()
	
public:
	USpellCasterComponent();

	void InitSpells();
	void CastSpell();
	void ChangeSpell(int slot);
	virtual void CycleSpell();

	void BindCastStartLocation(TFunction<const FVector()> func);
	void BindCastStartForward(TFunction<const FVector()> func);

	//---- HELPERS ----
	AActor* GetSpellOwner() noexcept override;
	const virtual FVector GetSpellOwnerLocation() noexcept override;
	const virtual FVector GetSpellOwnerForward() noexcept override;
	const virtual FVector GetCastStartLocation() noexcept override;
	const virtual FVector GetCastStartForward() noexcept override;
	ISpell* GetActiveSpell() noexcept;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, Category = "Test")
	TArray<TObjectPtr<USpellData>> _spellData;

	UPROPERTY()
	TScriptInterface<ISpell> _spell;

	UPROPERTY()
	TArray<TScriptInterface<ISpell>> _spells;

	int _currentSpellIndex = 0;

	FGetCastStart _castStartLocation;
	FGetCastForward _castStartForward;
};
