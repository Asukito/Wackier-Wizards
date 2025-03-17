// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellDecorator.h"
#include "TrailSpellDecorator.generated.h"

/**
 * 
 */
UCLASS()
class WACKIER_WIZARDS_API UTrailSpellDecorator : public USpellDecorator
{
	GENERATED_BODY()

//Applied to a ProjectileSpellDecorator. Initialises additional logic on the spawned projectile that periodically places an AOE effect along it's path.
public:
	class WACKIER_WIZARDS_API Builder
	{
		TWeakObjectPtr<UTrailSpellDecorator> decorator;

	public:

		Builder(ISpell* data)
		{
			decorator = NewObject<UTrailSpellDecorator>();
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
