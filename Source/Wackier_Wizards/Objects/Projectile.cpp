// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraEmitter.h"
#include "../Spells/ProjectileSpell.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	checkf(_staticMesh, TEXT("Projectile Static Mesh failed to initialise"));

	_staticMesh->SetSimulatePhysics(true);
	_staticMesh->SetVisibility(false);
	_staticMesh->SetCollisionProfileName(FName("Projectile"));
	SetRootComponent(_staticMesh);

	_niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	checkf(_niagara, TEXT("Projectile Niagara Component failed to initialise"));
	_niagara->SetupAttachment(_staticMesh);
}
void AProjectile::InitNiagara(UNiagaraSystem* niagara, UNiagaraSystem* collisionNiagara)
{
	if (collisionNiagara != nullptr)
	{
		_collisionEffect = collisionNiagara;
	}
	_niagara->SetAsset(niagara);
	_niagara->Activate();
}
void AProjectile::AddOwnerSpell(UProjectileSpell* spell)
{
	_spell = spell;
}
void AProjectile::AddIgnoreActor(AActor* actor)
{
	if (_ignore.Contains(actor) == true)
	{
		return;
	}

	_ignore.Add(actor);
}
void AProjectile::SetIsActive(bool isactive)
{
	_isActive = isactive;
}
void AProjectile::SetRange(float range)
{
	_maxDistance = range;
}
UStaticMeshComponent* AProjectile::GetStaticMesh()
{
	return _staticMesh;
}
void AProjectile::BeginInteractOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(_isActive == false || _ignore.Contains(OtherActor))
	{
		return;
	}

	if (_collisionEffect != nullptr)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), _collisionEffect, GetActorLocation(), FRotator::ZeroRotator);
	}

	if (_spell != nullptr)
	{
		_spell->ProcessHit(OtherActor, GetActorLocation());
		_spell = nullptr;
	}

	Destroy();
}
// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	_staticMesh->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::BeginInteractOverlap);
}

void AProjectile::CheckDistanceTravelled()
{
	if (_start == FVector::Zero())
	{
		_start = GetActorLocation();
	}

	FVector pos = GetActorLocation();

	if (pos.Length() >= _maxDistance)
	{
		Destroy();
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_isActive == false || _maxDistance <= 0.0f)
	{
		return;
	}

	CheckDistanceTravelled();
}

