// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "VRCharacter.generated.h"

class UWidgetComponent;
class UWidgetInteractionComponent;

UCLASS()
class WACKIER_WIZARDS_API AVRCharacter : public APlayerCharacter
{
	GENERATED_BODY()

//VR PlayerCharacter class. Currently overrides the GetCastStartForward as the spells will be spawned at the player's hand.
public:
	//Sets default values for this character's properties
	AVRCharacter();

	UFUNCTION(BlueprintCallable, Category = "VR")
	void SetInteractionComponent(UWidgetInteractionComponent* component);

	const FVector GetCastStartForward() override;

	//Location of right hand to spawn spell
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Player Spell")
	FVector rightHandLocation;

	// Right hand rotation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Spell")
	FRotator rightHandRotation;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UWidgetInteractionComponent> interactionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UWidgetComponent> widgetComponent;
};
