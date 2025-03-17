// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpellTrapBase.generated.h"

class ACharacter;
class USpellCasterComponent;

UCLASS()
class WACKIER_WIZARDS_API ASpellTrapBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpellTrapBase();

	virtual const FVector GetCastStartLocation();
	virtual const FVector GetCastStartForward();

	UFUNCTION()
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void InitSpellCasterComponent();

protected:	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpellCasterComponent> spellComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> staticMesh;

	TArray<TObjectPtr<ACharacter>> overlaps;
};
