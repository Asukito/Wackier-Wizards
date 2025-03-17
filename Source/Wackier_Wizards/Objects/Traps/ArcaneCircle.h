// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellTrapBase.h"
#include "ArcaneCircle.generated.h"

class ACharacter;
class USpellCasterComponent;
class UStaticMeshComponent;
class USpellData;

UCLASS()
class WACKIER_WIZARDS_API AArcaneCircle : public ASpellTrapBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArcaneCircle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpellData> _spell;
};
