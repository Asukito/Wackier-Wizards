// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageOnOverlapComponent.generated.h"

class UBoxComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WACKIER_WIZARDS_API UDamageOnOverlapComponent : public UActorComponent
{
	GENERATED_BODY()

//Component that can be attached to an actor, collision with the collider deals damage OnOverlap
public:	
	// Sets default values for this component's properties
	UDamageOnOverlapComponent();

	void Init();

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBoxComponent> _collider;
	UPROPERTY(EditDefaultsOnly)
	float _damagePercent;
};
