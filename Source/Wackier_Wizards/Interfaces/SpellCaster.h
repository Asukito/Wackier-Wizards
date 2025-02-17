// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SpellCaster.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class USpellCaster : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WACKIER_WIZARDS_API ISpellCaster
{
	GENERATED_BODY()

public:
	virtual AActor* GetSpellOwner() noexcept { return nullptr; };
	const virtual FVector GetSpellOwnerLocation() noexcept { return FVector::Zero(); };
	const virtual FVector GetSpellOwnerForward() noexcept { return FVector::Zero(); };
	const virtual FVector GetCastStartLocation() noexcept { return FVector::Zero(); };
	const virtual FVector GetCastStartForward() noexcept { return FVector::Zero(); };

};
