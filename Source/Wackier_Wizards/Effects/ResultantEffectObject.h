// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ResultantEffectObject.generated.h"

class UResultantEffectData;
class UEffectData;

UCLASS()
class WACKIER_WIZARDS_API UResultantEffectObject : public UObject
{
	GENERATED_BODY()
	
//Object that is created using ResultantEffect data, created and stored in ResultantEffectContainer at runtime
public:
	void Init(UResultantEffectData* data);

	UEffectData* CheckIfValid(FString nameOne, FString nameTwo);
private:
	UPROPERTY()
	TObjectPtr<UEffectData> _effectOne;
	UPROPERTY()
	TObjectPtr<UEffectData> _effectTwo;
	UPROPERTY()
	TObjectPtr<UEffectData> _resultantEffect;
};
