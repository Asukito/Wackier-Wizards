// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpikeTrap.generated.h"

class UBoxComponent;
class USkeletalMeshComponent;
class UAnimSequenceBase;

UCLASS()
class WACKIER_WIZARDS_API ASpikeTrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpikeTrap();

	UFUNCTION()
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> _spikeMesh;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBoxComponent> _triggerBox;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimSequenceBase> _animation;

	TArray<TObjectPtr<ACharacter>> _overlaps;

	UPROPERTY(EditDefaultsOnly)
	int damage;

	UPROPERTY(EditDefaultsOnly)
	float _triggerCooldown;
	float _cooldownTimer;
};
