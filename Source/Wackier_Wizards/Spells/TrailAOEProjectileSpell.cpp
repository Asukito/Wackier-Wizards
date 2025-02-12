// Fill out your copyright notice in the Description page of Project Settings.


#include "TrailAOEProjectileSpell.h"
#include "../Objects/Projectile.h"
#include "../Interfaces/SpellCaster.h"
#include "SpellData.h"

void UTrailAOEProjectileSpell::CastSpell()
{
	USpellBase::CastSpell();

	TObjectPtr<AActor> owner = spellOwner->GetSpellOwner();

	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AProjectile* projectile = owner->GetWorld()->SpawnActor<AProjectile>(AProjectile::StaticClass(), spellOwner->GetCastStartLocation(), FRotator::ZeroRotator, spawnParams);
	projectile->AddIgnoreActor(owner);
	projectile->AddOwnerSpell(this);
	projectile->InitNiagara(spellData->spellNiagara, spellData->collisionNiagara);
	projectile->InitTrail(spellData->trailEffect);
	projectile->SetRange(spellData->range);

	FVector unitDirection = spellOwner->GetCastStartForward();

	projectile->SetIsActive(true);
	projectile->ApplyForce(false, unitDirection, spellData->speed);
}
