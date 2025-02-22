// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interfaces/Effectable.h"
#include "../Interfaces/Damageable.h"
#include "PracticeDummy.generated.h"

class UStaticMeshComponent;
class UCapsuleComponent;
class UEffectsComponent;

UCLASS()
class WACKIER_WIZARDS_API APracticeDummy : public AActor, public IEffectable, public IDamageable
{
	GENERATED_BODY()

//An actor that can be damaged and effected. Created at the start of development for spell/effect testing. 
public:	
	// Sets default values for this actor's properties
	APracticeDummy();

	using IDamageable::TakeDamage;

	bool TakeDamage(int amount, FString source) override;
	void AddEffect(UEffectData* effect) override;

	IDamageable* GetDamageableAccess() override;
	IHealth* GetHealthAccess() override;
	void AdjustWalkSpeed(float percent) override;
	bool HasMovementComponent() override
	{
		return false;
	}
	bool HasEffect(FString effectName) override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> _staticMesh;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UCapsuleComponent> _collider;
	UPROPERTY()
	TObjectPtr<UEffectsComponent> _effectComponent;
};
