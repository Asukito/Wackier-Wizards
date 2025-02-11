// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileSpell.h"
#include "../Objects/Projectile.h"
#include "../Interfaces/SpellCaster.h"
#include "SpellData.h"

void UProjectileSpell::CastSpell()
{
	USpellBase::CastSpell();

	TObjectPtr<AActor> owner = spellOwner->GetSpellOwner();

	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AProjectile* projectile = owner->GetWorld()->SpawnActor<AProjectile>(AProjectile::StaticClass(), spellOwner->GetCastStartLocation(), FRotator::ZeroRotator, spawnParams);
	projectile->AddIgnoreActor(owner);
	projectile->AddOwnerSpell(this);
	projectile->InitNiagara(spellData->spellNiagara, spellData->collisionNiagara);
	projectile->SetRange(spellData->range);

	FVector unitDirection = spellOwner->GetCastStartForward();

	projectile->SetIsActive(true);
	projectile->ApplyForce(spellData->useGravity, unitDirection, spellData->speed);
}

void UProjectileSpell::ProcessHit(AActor* hit, FVector projectileLocation)
{
	HandleInterfaceFunctions(hit);
}
