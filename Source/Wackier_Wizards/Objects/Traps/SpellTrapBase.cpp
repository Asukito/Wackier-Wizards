// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellTrapBase.h"
#include "../../Components/SpellCasterComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"

// Sets default values
ASpellTrapBase::ASpellTrapBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	checkf(staticMesh, TEXT("Spell Trap StaticMeshComponent failed to initialise"));
	staticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetRootComponent(staticMesh);

	spellComponent = CreateDefaultSubobject<USpellCasterComponent>(TEXT("Spell Caster Component"));
	checkf(spellComponent, TEXT("Spell Turret SpellCasterComponent failed to initalise"));
}

const FVector ASpellTrapBase::GetCastStartLocation()
{
	return GetActorLocation();
}

const FVector ASpellTrapBase::GetCastStartForward()
{
	return GetActorForwardVector();
}

void ASpellTrapBase::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr || overlaps.Contains(OtherActor) == true)
	{
		return;
	}

	if (ACharacter* character = Cast<ACharacter>(OtherActor))
	{
		overlaps.Add(character);
	}
}

void ASpellTrapBase::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == nullptr || overlaps.Contains(OtherActor) == false)
	{
		return;
	}

	if (ACharacter* character = Cast<ACharacter>(OtherActor))
	{
		overlaps.Remove(character);
	}
}

// Called when the game starts or when spawned
void ASpellTrapBase::BeginPlay()
{
	Super::BeginPlay();
}

void ASpellTrapBase::InitSpellCasterComponent()
{
	spellComponent->InitSpells();
	spellComponent->BindCastStartLocation([this]() { return GetCastStartLocation(); });
	spellComponent->BindCastStartForward([this]() { return GetCastStartForward(); });
}

// Called every frame
void ASpellTrapBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (overlaps.Num() == 0)
	{
		return;
	}

	spellComponent->CastSpell();
}

