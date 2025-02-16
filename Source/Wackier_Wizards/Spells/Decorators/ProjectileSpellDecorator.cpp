// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileSpellDecorator.h"
#include "../../Objects/Projectile.h"
#include "../../Interfaces/SpellCaster.h"
#include "../SpellData.h"
#include "../SpellBase.h"

bool UProjectileSpellDecorator::CastSpell()
{
	if (spell->CastSpell() == false)
	{
		return false;
	}

	TObjectPtr<AActor> owner = spellOwner->GetSpellOwner();

	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AProjectile* projectile = owner->GetWorld()->SpawnActor<AProjectile>(AProjectile::StaticClass(), spellOwner->GetCastStartLocation(), FRotator::ZeroRotator, spawnParams);
	projectile->AddIgnoreActor(owner);

	if (ownerSpell != nullptr)
	{
		projectile->AddOwnerSpell(ownerSpell.GetInterface());
	}
	else
	{
		projectile->AddOwnerSpell(this);
	}

	projectile->InitNiagara(spellData->spellNiagara);
	projectile->SetRange(spellData->range);

	GetBaseSpell()->SetProjectile(projectile);

	FVector unitDirection = spellOwner->GetCastStartForward();

	projectile->SetIsActive(true);
	projectile->ApplyForce(spellData->useGravity, unitDirection, spellData->speed);

	return true;
}

void UProjectileSpellDecorator::ProcessHit(AActor* hit, FVector location)
{
	spell->ProcessHit(hit, location);
}

USpellBase* UProjectileSpellDecorator::GetBaseSpell()
{
	return spell->GetBaseSpell();
}
