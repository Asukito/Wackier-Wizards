// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "AOEEffectActor.h"
#include "Engine/StaticMesh.h"
#include "../Effects/EffectData.h"
#include "../Effects/Auras/ShieldAuraEffect.h"
#include "../Spells/SpellData.h"
#include "../Interfaces/SpellCaster.h"
#include "GameFramework/Character.h"

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

	_staticMesh->SetSimulatePhysics(true);
	_staticMesh->SetVisibility(false);
	_staticMesh->SetCollisionProfileName(FName("Projectile"));
	SetRootComponent(_staticMesh);

	_niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	checkf(_niagara, TEXT("Projectile Niagara Component failed to initialise"));
	_niagara->SetupAttachment(_staticMesh);
	_niagara->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

//Initialises functionality for creating an effect trail
void AProjectile::InitTrail()
{
	_trailEffect = _spellData->trailEffect;
	_trailInterval = _spellData->trailSize / 2;
	_lastLocation = GetActorLocation();

	_hasTrail = true;
}

void AProjectile::InitPenetrate()
{
	_canPenetrate = true;
	_maxPenetrateAmount = _spellData->penetrateLimit;
	_penetrateAmount = _maxPenetrateAmount;
	_damageLossPerIndex = _spellData->damageLossPerHit;
}

void AProjectile::InitNiagara(UNiagaraSystem* niagara)
{
	_niagara->SetAsset(niagara);
	_niagara->Activate();
}
void AProjectile::AddOwnerSpell(ISpell* spell)
{
	_spell = spell->_getUObject();
	_spellData = _spell->GetSpellData();
	_staticMesh->SetRelativeScale3D(FVector(_spellData->projectileSize));
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

	_staticMesh->SetEnableGravity(gravity);

	_velocity = unitDirection * speed;
	_staticMesh->SetPhysicsLinearVelocity(_velocity);
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

	if (_spell == nullptr)
	{
		Destroy();
	}

	if (_canPenetrate == false || Cast<ACharacter>(OtherActor) == nullptr)
	{
		_spell->ProcessHit(OtherActor, GetActorLocation(), 0);
		_spell = nullptr;
		Destroy();

		return;
	}

	int damageAdjustment = (_maxPenetrateAmount - _penetrateAmount) * -(_damageLossPerIndex);
	_spell->ProcessHit(OtherActor, GetActorLocation(), damageAdjustment);

	if (_penetrateAmount <= 0)
	{
		_spell = nullptr;
		Destroy();
		return;
	}

	_penetrateAmount -= 1;
}
// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	_staticMesh->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::BeginInteractOverlap);
}

//Destroys the projectile if the distance travelled exceeds the maxDistance.
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

//Spawns an AOE actor
void AProjectile::PlaceAOE()
{
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	TObjectPtr<AAOEEffectActor> actor = GetWorld()->SpawnActor<AAOEEffectActor>(AAOEEffectActor::StaticClass(), GetActorLocation(), FRotator::ZeroRotator, params);
	AddIgnoreActor(actor);
	actor->AddIgnoredActor(_spell->GetSpellOwner()->GetSpellOwner());

	actor->Init(_trailEffect, _spellData->trailLifetime, _spellData->trailSize, _spellData->doPullEffect);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_isActive == false || _maxDistance <= 0.0f)
	{
		return;
	}

	if (_staticMesh->GetPhysicsLinearVelocity() == FVector::Zero())
	{
		_staticMesh->SetPhysicsLinearVelocity(_velocity);
	}

	CheckDistanceTravelled();

	if (_hasTrail == false)
	{
		return;
	}

	//If the distance between the lastLocation and currentLocation is greater than the trailInterval. Execute PlaceAOE().
	FVector location = GetActorLocation();

	if ((location - _lastLocation).Length() >= _trailInterval)
	{
		PlaceAOE();
		_lastLocation = location;
	}
}

