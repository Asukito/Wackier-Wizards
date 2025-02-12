// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "EnhancedPlayerInput.h"
#include "../../Interfaces/Effectable.h"
#include "../../Interfaces/Damageable.h"
#include "../../Interfaces/SpellCaster.h"
#include "../../Interfaces/Health.h"
#include "../../Spells/SpellType.h"
#include "VRCharacter.generated.h"

class UCameraComponent;
class AWWPlayerController;
class UStaticMeshComponent;
class UHealthComponent;
class USpellData;
class USpellBase;
class UEffectsComponent;

UCLASS()
class WACKIER_WIZARDS_API AVRCharacter : public APlayerCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVRCharacter();

	// Input mapping context for VRCharacter
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Mapping")
	//class UInputMappingContext* InputMappingContext;

	const FVector GetCastStartForward() noexcept override;

	//location of right hand to spawn spell
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Player Spell")
	FVector rightHandLocation;


public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
