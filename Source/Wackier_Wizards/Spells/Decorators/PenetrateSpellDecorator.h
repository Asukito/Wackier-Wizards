// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellDecorator.h"
#include "PenetrateSpellDecorator.generated.h"

/**
 * 
 */
UCLASS()
class WACKIER_WIZARDS_API UPenetrateSpellDecorator : public USpellDecorator
{
	GENERATED_BODY()

//AOE Effect decorator. Generates an AOE Effect at the collision location passed in through ProcessHit.
public:
	class WACKIER_WIZARDS_API Builder
	{
		TWeakObjectPtr<UPenetrateSpellDecorator> decorator;

	public:

		Builder(ISpell* data)
		{
			decorator = NewObject<UPenetrateSpellDecorator>();
			decorator->Decorate(data);
			data->SetOwnerSpell(decorator.Get());
		}
		ISpell* Build()
		{
			return decorator.Get();
		}
	};

	virtual void FireProjectile(FVector direction) override;
};
