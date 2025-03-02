// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellTrap.h"
#include "../Components/SpellCasterComponent.h"

// Sets default values
ASpellTrap::ASpellTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	sphereCollider->SetSphereRadius(100.0f);
	sphereCollider->SetCollisionProfileName(TEXT("Spell"));
	sphereCollider->SetGenerateOverlapEvents(true);
	sphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ASpellTrap::OnSpellTrapOverlap);
	sphereCollider->SetupAttachment(RootComponent);

	spellCasterComponent = CreateDefaultSubobject<USpellCasterComponent>(TEXT("SpellCaster Component"));
	checkf(spellCasterComponent, TEXT("Player SpellCasterComponent failed to initialise"));


}

// Called when the game starts or when spawned
void ASpellTrap::BeginPlay()
{
	Super::BeginPlay();

	spellCasterComponent->InitSpells();

	//Do spell location binds
}

// Called every frame
void ASpellTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpellTrap::OnSpellTrapOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if the overlapped actor is the player then fire off a spell
	if (OtherActor->ActorHasTag("Player"))
	{
		spellCasterComponent->CastSpell();
		UE_LOG(LogTemp, Warning, TEXT("BOOM"));
	}
}

