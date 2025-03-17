// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellDecorator.h"
#include "BeamSpellDecorator.generated.h"

class UNiagaraComponent;

UCLASS()
class WACKIER_WIZARDS_API UBeamSpellDecorator : public USpellDecorator
{
	GENERATED_BODY()

//A hitscan variation that has no cooldown. Logic is separated as decorating a Hitscan with the Beam logic would cause issues with further decorators.
//Mana will be implemented to limit the usage of beam spells (as well as others)
public:
	class WACKIER_WIZARDS_API Builder
	{
		TWeakObjectPtr<UBeamSpellDecorator> decorator;

	public:

		Builder(ISpell* data)
		{
			decorator = NewObject<UBeamSpellDecorator>();
			decorator->Decorate(data);
			data->SetOwnerSpell(decorator.Get());
		}
		ISpell* Build()
		{
			return decorator.Get();
		}
	};

	virtual bool CastSpell() override;

	virtual void Update(float deltaTime) override;
private:
	TObjectPtr<UNiagaraComponent> _beam;

	float _timer;
};
