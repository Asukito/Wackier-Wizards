// Fill out your copyright notice in the Description page of Project Settings.


#include "VoidObject.h"
#include "../Components/DamageOnOverlapComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AVoidObject::AVoidObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	_staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	checkf(_staticMesh, TEXT("VoidObject Static Mesh failed to intialise"));
	_staticMesh->SetCollisionProfileName(FName("NoCollision"));
	SetRootComponent(_staticMesh);

	_damageComponent = CreateDefaultSubobject<UDamageOnOverlapComponent>(TEXT("Damage Component"));
	checkf(_damageComponent, TEXT("VoidObject Damage Component failed to intialise"));
	_damageComponent->Init();
}

// Called when the game starts or when spawned
void AVoidObject::BeginPlay()
{
	Super::BeginPlay();
	
}

