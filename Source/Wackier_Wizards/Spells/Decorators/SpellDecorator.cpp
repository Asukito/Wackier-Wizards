// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellDecorator.h"
#include "../../Interfaces/SpellCaster.h"
#include "../../Objects/Projectile.h"
#include "../SpellData.h"
#include "../SpellBase.h"

void USpellDecorator::Decorate(ISpell* decorate)
{
	if (decorate == nullptr)
	{
		return;
	}

	spell = decorate->_getUObject();
	spellData = spell->GetSpellData();
	spellOwner = spell->GetSpellOwner()->_getUObject();
}

void USpellDecorator::SetOwnerSpell(ISpell* owner)
{
	ownerSpell = owner->_getUObject();
}

bool USpellDecorator::CastSpell()
{
	return spell->CastSpell();
}

void USpellDecorator::Update(float deltaTime)
{
	spell->Update(deltaTime);
}

void USpellDecorator::ProcessHit(AActor* hit, FVector location)
{
	spell->ProcessHit(hit, location);
}

const FString USpellDecorator::GetSpellName()
{
	return spell->GetSpellName();
}

const float USpellDecorator::GetSpellRange()
{
	return spell->GetSpellRange();
}

USpellData* USpellDecorator::GetSpellData()
{
	return spell->GetSpellData();
}

ISpellCaster* USpellDecorator::GetSpellOwner()
{
	return spell->GetSpellOwner();
}

USpellBase* USpellDecorator::GetBaseSpell()
{
	if (spell == nullptr)
	{
		return nullptr;
	}

	return spell->GetBaseSpell();
}

ISpell* USpellDecorator::GetDecorator()
{
	if (ownerSpell == nullptr)
	{
		return this;
	}

	return ownerSpell->GetDecorator();
}

void USpellDecorator::FireLineTrace(AActor* owner, FVector start, FVector end, FVector& OutEnd)
{
	FHitResult hit;
	FCollisionQueryParams params;
	params.AddIgnoredActor(owner);

	if (owner->GetWorld()->LineTraceSingleByChannel(hit, start, end, ECollisionChannel::ECC_WorldStatic, params))
	{
		DrawDebugLine(owner->GetWorld(), start, hit.Location, FColor::Green, false, 2.0f);

		GetDecorator()->ProcessHit(hit.GetActor(), hit.Location);
	}
	else
	{
		DrawDebugLine(owner->GetWorld(), start, end, FColor::Green, false, 2.0f);
	}

	OutEnd = end;
}

void USpellDecorator::FireProjectile(FVector direction)
{
	TObjectPtr<AActor> owner = spellOwner->GetSpellOwner();

	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AProjectile* projectile = owner->GetWorld()->SpawnActor<AProjectile>(AProjectile::StaticClass(), spellOwner->GetCastStartLocation(), FRotator::ZeroRotator, spawnParams);
	projectile->AddIgnoreActor(owner);

	projectile->AddOwnerSpell(GetDecorator());

	projectile->InitNiagara(spellData->spellNiagara);
	projectile->SetRange(spellData->range);

	GetBaseSpell()->SetProjectile(projectile);

	projectile->SetIsActive(true);
	projectile->ApplyForce(spellData->useGravity, direction, spellData->speed);
}

bool USpellDecorator::IsOnCooldown()
{
	return spell->IsOnCooldown();
}

void USpellDecorator::HandleEffects(IEffectable* target)
{
	spell->HandleEffects(target);
}

void USpellDecorator::HandleInterfaceFunctions(AActor* actor)
{
	spell->HandleInterfaceFunctions(actor);
}
