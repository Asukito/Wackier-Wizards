// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FalseFloorTrap.generated.h"

class UBoxComponent;

UCLASS()
class WACKIER_WIZARDS_API AFalseFloorTrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFalseFloorTrap();

	UFUNCTION()
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> _staticMesh;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBoxComponent> _triggerBox;

	float _resetTimer;

	bool _triggered;
};
