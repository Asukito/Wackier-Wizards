// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellDecorator.h"
#include "CasterEffectSpellDecorator.generated.h"

/**
 * 
 */
UCLASS()
class WACKIER_WIZARDS_API UCasterEffectSpellDecorator : public USpellDecorator
{
	GENERATED_BODY()
	
public:
	class WACKIER_WIZARDS_API Builder
	{
		TWeakObjectPtr<UCasterEffectSpellDecorator> decorator;

	public:

		Builder(ISpell* data)
		{
			decorator = NewObject<UCasterEffectSpellDecorator>();
			decorator->Decorate(data);
			data->SetOwnerSpell(decorator.Get());
		}
		ISpell* Build()
		{
			return decorator.Get();
		}
	};

	virtual bool CastSpell() override;
};
