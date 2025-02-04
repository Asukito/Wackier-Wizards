// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileSpell.h"
#include "../Objects/Projectile.h"
#include "../Interfaces/SpellCaster.h"
#include "../Interfaces/Damageable.h"
#include "Components/StaticMeshComponent.h"
#include "SpellData.h"

void UProjectileSpell::CastSpell()
{
	USpellBase::CastSpell();

	AActor* owner = spellOwner->GetSpellOwner();

	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AProjectile* projectile = owner->GetWorld()->SpawnActor<AProjectile>(*spellData->projectileDefault, spellOwner->GetCastStartLocation(), FRotator::ZeroRotator, spawnParams);
	projectile->AddIgnoreActor(owner);
	projectile->AddOwnerSpell(this);
	projectile->InitNiagara(spellData->spellNiagara, spellData->collisionNiagara);
	projectile->SetRange(spellData->range);

	FVector unitDirection = spellOwner->GetSpellOwnerForward();

	projectile->GetStaticMesh()->SetEnableGravity(spellData->useGravity);
	projectile->GetStaticMesh()->SetPhysicsLinearVelocity(unitDirection * spellData->speed);

	projectile->SetIsActive(true);
}

void UProjectileSpell::ProcessHit(AActor* hit, FVector projectileLocation)
{
	if (IDamageable* target = Cast<IDamageable>(hit))
	{
		target->TakeDamage(spellData->potency, spellData->name);
	}
}
