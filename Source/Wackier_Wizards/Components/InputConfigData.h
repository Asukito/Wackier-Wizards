// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "InputConfigData.generated.h"

/**
 * 
 */
UCLASS()
class WACKIER_WIZARDS_API UInputConfigData : public UDataAsset
{
	GENERATED_BODY()


public:

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UInputAction* PlayerMove;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UInputAction* PlayerChangeSpell;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UInputAction* PlayerShootSpell;
};
