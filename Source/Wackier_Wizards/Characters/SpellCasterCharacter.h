// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "../Interfaces/SpellCaster.h"
#include "SpellCasterCharacter.generated.h"

class USpellBase;
class USpellData;

UCLASS()
class WACKIER_WIZARDS_API ASpellCasterCharacter : public ABaseCharacter, public ISpellCaster
{
	GENERATED_BODY()
	
public:
	ASpellCasterCharacter();

	void InitSpells();
	void CastSpell();
	UFUNCTION(BlueprintCallable)
	void ChangeSpell(int slot);
	virtual void CycleSpell();

	//---- HELPERS ----
	AActor* GetSpellOwner() noexcept override;
	const virtual FVector GetSpellOwnerLocation() noexcept override;
	const virtual FVector GetSpellOwnerForward() noexcept override;
	const virtual FVector GetCastStartLocation() noexcept override;
	const virtual FVector GetCastStartForward() noexcept override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Test")
	TArray<TObjectPtr<USpellData>> _spellData;

	UPROPERTY()
	TObjectPtr<USpellBase> _spell;

	UPROPERTY()
	TArray<TObjectPtr<USpellBase>> _spells;

	int _currentSpellIndex = 0;
};
