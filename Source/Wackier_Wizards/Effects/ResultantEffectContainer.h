

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ResultantEffectContainer.generated.h"

class UResultantEffectData;
class UResultantEffectObject;
class UEffectData;

UCLASS()
class WACKIER_WIZARDS_API AResultantEffectContainer : public AActor
{
	GENERATED_BODY()
	
//Data container for storing ResultantEffects
public:	
	// Sets default values for this actor's properties
	AResultantEffectContainer();

	UEffectData* CheckIfValid(FString nameOne, FString nameTwo);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TArray<TObjectPtr<UResultantEffectData>> _resultantEffects;

	UPROPERTY()
	TArray<TObjectPtr<UResultantEffectObject>> _resultantObjects;
};
