// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamSpellDecorator.h"
#include "../../Interfaces/SpellCaster.h"
#include "../../Spells/SpellData.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "../SpellBase.h"

bool UBeamSpellDecorator::CastSpell()
{
	if (spell->CastSpell() == false)
	{
		return false;
	}

	_timer = 0.2f;

	TObjectPtr<AActor> owner = spellOwner->GetSpellOwner();
	FVector start = spellOwner->GetCastStartLocation();
	FVector end = ((spellOwner->GetCastStartForward() * spellData->range) + start);

	if (_beam == nullptr)
	{
		_beam = UNiagaraFunctionLibrary::SpawnSystemAtLocation(spellOwner->GetSpellOwner()->GetWorld(), spellData->spellNiagara, start, spellOwner->GetCastStartForward().Rotation());
	}
	else
	{
		_beam->SetWorldLocation(start);
		_beam->SetWorldRotation(spellOwner->GetCastStartForward().Rotation());
	}

	FHitResult hit;
	FCollisionQueryParams params;
	params.AddIgnoredActor(owner);

	if (owner->GetWorld()->LineTraceSingleByChannel(hit, start, end, ECollisionChannel::ECC_WorldStatic, params))
	{
		DrawDebugLine(owner->GetWorld(), start, hit.Location, FColor::Green, false, 2.0f);
		_beam->SetVariableVec3(FName("TraceEnd"), hit.Location);

		if (ownerSpell != nullptr)
		{
			ownerSpell->ProcessHit(hit.GetActor(), hit.Location);
		}
		else
		{
			ProcessHit(hit.GetActor(), hit.Location);
		}
	}
	else
	{
		_beam->SetVectorParameter(FName("TraceEnd"), end);
		DrawDebugLine(owner->GetWorld(), start, end, FColor::Green, false, 2.0f);
	}

	return true;
}

void UBeamSpellDecorator::Update(float deltaTime)
{
	_timer -= deltaTime;

	if (_timer < 0.0f && _beam != nullptr)
	{
		_beam->DestroyComponent();
		_beam = nullptr;
	}
}

USpellBase* UBeamSpellDecorator::GetBaseSpell()
{
	return spell->GetBaseSpell();
}

ISpell* UBeamSpellDecorator::GetOwnerSpell()
{
	if (ownerSpell == nullptr)
	{
		return nullptr;
	}

	return ownerSpell.GetInterface();
}
