// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UStaticMeshComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UNiagaraEmitter;
class UProjectileSpell;

UCLASS()
class WACKIER_WIZARDS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	void InitNiagara(UNiagaraSystem* niagara, UNiagaraSystem* collisionNiagara = nullptr);
	void AddOwnerSpell(UProjectileSpell* spell);
	void AddIgnoreActor(AActor* actor);
	void SetIsActive(bool isactive);
	void SetRange(float range);

	UStaticMeshComponent* GetStaticMesh();

	UFUNCTION()
	void BeginInteractOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void CheckDistanceTravelled();

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> _staticMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraComponent> _niagara;
	UPROPERTY()
	TObjectPtr<UNiagaraSystem> _collisionEffect;
	UPROPERTY()
	TObjectPtr<UProjectileSpell> _spell;

	TArray<TWeakObjectPtr<AActor>> _ignore;


	FVector _start;
	float _maxDistance;
	bool _isActive;
};
