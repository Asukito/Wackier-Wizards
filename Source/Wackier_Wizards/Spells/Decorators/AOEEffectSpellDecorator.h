// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellDecorator.h"
#include "AOEEffectSpellDecorator.generated.h"

/**
 * 
 */
UCLASS()
class WACKIER_WIZARDS_API UAOEEffectSpellDecorator : public USpellDecorator
{
	GENERATED_BODY()
	
//AOE Effect decorator. Generates an AOE Effect at the collision location passed in through ProcessHit.
public:
	class WACKIER_WIZARDS_API Builder
	{
		TWeakObjectPtr<UAOEEffectSpellDecorator> decorator;

	public:

		Builder(ISpell* data)
		{
			decorator = NewObject<UAOEEffectSpellDecorator>();
			decorator->Decorate(data);
			data->SetOwnerSpell(decorator.Get());
		}
		ISpell* Build()
		{
			return decorator.Get();
		}
	};

	void ProcessHit(AActor* hit, FVector location, int damageAdjustment = 0) override;
};
