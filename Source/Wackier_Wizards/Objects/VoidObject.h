// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VoidObject.generated.h"

class UDamageOnOverlapComponent;
class UStaticMeshComponent;

UCLASS()
class WACKIER_WIZARDS_API AVoidObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVoidObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> _staticMesh;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UDamageOnOverlapComponent> _damageComponent;
};
