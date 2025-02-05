// Fill out your copyright notice in the Description page of Project Settings.


#include "PracticeDummy.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "../Components/EffectsComponent.h"

// Sets default values
APracticeDummy::APracticeDummy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	_collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	checkf(_collider, TEXT("Pracice Dummy Collider failed to initialise"));
	_collider->SetCollisionProfileName(FName("Damageable"));
	SetRootComponent(_collider);

	_staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	checkf(_staticMesh, TEXT("Practice Dummy StaticMesh failed to initialise"));
	_staticMesh->SetCollisionProfileName(FName("NoCollision"));
	_staticMesh->SetupAttachment(_collider);

	_effectComponent = CreateDefaultSubobject<UEffectsComponent>(TEXT("Effects Component"));
	checkf(_effectComponent, TEXT("Practice Dummy EffectsComponent failed to initialise"));
}

void APracticeDummy::TakeDamage(int amount, FString source)
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("%s: Taken %i damage from %s"), *GetName(), amount, *source));
}

void APracticeDummy::AddEffect(Effect effect)
{
	_effectComponent->CreateAndAddEffect(effect);
}

IDamageable* APracticeDummy::GetDamageableAccess()
{
	return Cast<IDamageable>(this);
}

IHealth* APracticeDummy::GetHealthAccess()
{
	return nullptr;
}

// Called when the game starts or when spawned
void APracticeDummy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APracticeDummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

