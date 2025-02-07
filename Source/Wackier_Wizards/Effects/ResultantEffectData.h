

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
	TObjectPtr<UEffectData> conditionOne;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UEffectData> conditionTwo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UEffectData> resultantEffect;
};