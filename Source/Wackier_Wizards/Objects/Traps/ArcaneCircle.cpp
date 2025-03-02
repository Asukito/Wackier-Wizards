// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcaneCircle.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "../../Components/SpellCasterComponent.h"
#include "../../Spells/SpellBase.h"
#include "../../Spells/SpellData.h"

// Sets default values
AArcaneCircle::AArcaneCircle() : ASpellTrapBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	staticMesh->SetCollisionProfileName(FName("Aura"));
	staticMesh->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void AArcaneCircle::BeginPlay()
{
	ASpellTrapBase::BeginPlay();

	if (_spell == nullptr || _spell->type != ESpellType::SELF || _spell->isAOE == false)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Black, FString::Printf(TEXT("ARCANE CIRCLE HAS INVALID SPELL TYPE")));
		return;
	}

	TObjectPtr<USpellData> copy = DuplicateObject(_spell, this);
	copy->aoeRange = staticMesh->GetRelativeScale3D().X * 50;

	TArray<USpellData*> spells;
	spells.Add(copy);

	spellComponent->PopulateSpells(spells);

	InitSpellCasterComponent();

	staticMesh->OnComponentBeginOverlap.AddDynamic(this, &AArcaneCircle::BeginOverlap);
	staticMesh->OnComponentEndOverlap.AddDynamic(this, &AArcaneCircle::EndOverlap);
}

