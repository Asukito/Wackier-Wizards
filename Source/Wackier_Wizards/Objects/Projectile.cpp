// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraEmitter.h"
#include "../Spells/ProjectileSpell.h"
#include "../Objects/AOEActor.h"
#include "Engine/StaticMesh.h"
#include "../Effects/EffectData.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	checkf(_staticMesh, TEXT("Projectile Static Mesh failed to initialise"));

	ConstructorHelpers::FObjectFinder<UStaticMesh>
		mesh(TEXT("'/Game/CAME_WITH_PROJECT/StarterContent/Props/MaterialSphere.MaterialSphere'"));

	if (mesh.Succeeded())
	{
		_staticMesh->SetStaticMesh(mesh.Object);
	}

	_staticMesh->Mobility = EComponentMobility::Movable;
	_staticMesh->CanCharacterStepUpOn = ECB_No;
	_staticMesh->SetSimulatePhysics(true);
	_staticMesh->SetVisibility(false);
	_staticMesh->SetCollisionProfileName(FName("Projectile"));
	SetRootComponent(_staticMesh);

	_niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	checkf(_niagara, TEXT("Projectile Niagara Component failed to initialise"));
	_niagara->SetupAttachment(_staticMesh);
}

void AProjectile::InitTrail(UEffectData* trailEffect)
{
	_trailEffect = trailEffect;
	_trailInterval = _trailEffect->bonusRange / 2;
	_lastLocation = GetActorLocation();

	_hasTrail = true;
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
void AProjectile::ApplyForce(bool gravity, FVector unitDirection, float speed)
{
	_startPos = GetActorLocation();

	_staticMesh->SetRelativeScale3D(FVector(1.0f));
	_staticMesh->SetEnableGravity(gravity);
	FVector force = unitDirection * speed;
	_staticMesh->SetPhysicsLinearVelocity(force);
	_niagara->SetRelativeRotation(unitDirection.Rotation());
}
UStaticMeshComponent* AProjectile::GetStaticMesh()
{
	return _staticMesh;
}
void AProjectile::BeginInteractOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(_isActive == false || _ignore.Contains(OtherActor) || OtherActor->Tags.Contains("Effect"))
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

	FVector pos = GetActorLocation() - _startPos;

	if (pos.Length() >= _maxDistance)
	{
		Destroy();
	}
}

void AProjectile::PlaceAOE()
{
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	TObjectPtr<AAOEActor> actor = GetWorld()->SpawnActor<AAOEActor>(AAOEActor::StaticClass(), GetActorLocation(), FRotator::ZeroRotator, params);
	AddIgnoreActor(actor);
	actor->Init(_trailEffect);
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

	if (_hasTrail == false)
	{
		return;
	}

	FVector location = GetActorLocation();

	if ((location - _lastLocation).Length() >= _trailInterval)
	{
		PlaceAOE();
		_lastLocation = location;
	}
}

