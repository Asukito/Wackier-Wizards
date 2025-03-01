

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ResultantEffectData.generated.h"

class UEffectData;

UCLASS()
class WACKIER_WIZARDS_API UResultantEffectData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString conditionOne;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString conditionTwo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UEffectData> resultantEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool isRandom;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "isRandom == true", EditConditionHides))
	float chance;
};