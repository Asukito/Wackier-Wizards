// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpellBase.h"
#include "SpellData.h"
#include "Components/SphereComponent.h"
#include "SpellTrap.generated.h"

class USpellCasterComponent;
UCLASS()
class WACKIER_WIZARDS_API ASpellTrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpellTrap();

	//reference to the spell base but allowing children of the spell base to be used for polymorphism
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	USpellBase* spellBase;

	//reference to the spell data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	USpellData* spellData;

	//spellcaster component reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	TObjectPtr<USpellCasterComponent> spellCasterComponent;

	//reference to sphere collider
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spell")
	class USphereComponent* sphereCollider;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//function to handle the spell trap collision
	UFUNCTION()
	void OnSpellTrapOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
