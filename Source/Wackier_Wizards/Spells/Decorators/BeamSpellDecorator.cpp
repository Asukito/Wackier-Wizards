// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamSpellDecorator.h"
#include "../../Interfaces/SpellCaster.h"
#include "../../Spells/SpellData.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "../SpellBase.h"

//Generates a linetrace using the spells parameters. A NiagaraComponent is created and initialised if one doesn't exist. If one does, the TraceStart and TraceEnd positions are updated. 
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

	FVector hitEnd;

	FireLineTrace(owner, start, end, hitEnd);
	_beam->SetVariableVec3(FName("TraceEnd"), hitEnd);

	return true;
}

//_beam NiagaraComponent destroyed after a small delay. 
void UBeamSpellDecorator::Update(float deltaTime)
{
	_timer -= deltaTime;

	if (_timer < 0.0f && _beam != nullptr)
	{
		_beam->DestroyComponent();
		_beam = nullptr;
	}
}
