// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellTurret.h"
#include "Components/BoxComponent.h"

// Sets default values
ASpellTurret::ASpellTurret() : ASpellTrapBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	checkf(_triggerBox, TEXT("Spell Turret BoxComponent failed to initialise"));
	_triggerBox->SetupAttachment(staticMesh);
	_triggerBox->bHiddenInGame = false;
	_triggerBox->SetVisibility(true);
	_triggerBox->SetCollisionProfileName(FName("Aura"));
	_triggerBox->SetGenerateOverlapEvents(true);
	_triggerBox->SetupAttachment(RootComponent);

	_castLocation = CreateDefaultSubobject<UBoxComponent>(TEXT("Cast Location"));
	checkf(_triggerBox, TEXT("Spell Turret BoxComponent failed to initialise"));
	_castLocation->SetupAttachment(staticMesh);
	_castLocation->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

const FVector ASpellTurret::GetCastStartLocation()
{
	return _castLocation->GetComponentLocation();
}

// Called when the game starts or when spawned
void ASpellTurret::BeginPlay()
{
	ASpellTrapBase::BeginPlay();
	
	InitSpellCasterComponent();

	_triggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASpellTurret::BeginOverlap);
	_triggerBox->OnComponentEndOverlap.AddDynamic(this, &ASpellTurret::EndOverlap);
}
