// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileSpellDecorator.h"
#include "TrailSpellDecorator.generated.h"

/**
 * 
 */
UCLASS()
class WACKIER_WIZARDS_API UTrailSpellDecorator : public UProjectileSpellDecorator
{
	GENERATED_BODY()
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

	virtual bool CastSpell() override;

	virtual USpellBase* GetBaseSpell() override;
	virtual ISpell* GetOwnerSpell() override;
};
