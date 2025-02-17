// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellDecorator.h"
#include "KnockbackSpellDecorator.generated.h"

/**
 * 
 */
UCLASS()
class WACKIER_WIZARDS_API UKnockbackSpellDecorator : public USpellDecorator
{
	GENERATED_BODY()
	
public:
	class WACKIER_WIZARDS_API Builder
	{
		TWeakObjectPtr<UKnockbackSpellDecorator> decorator;

	public:

		Builder(ISpell* data)
		{
			decorator = NewObject<UKnockbackSpellDecorator>();
			decorator->Decorate(data);
			data->SetOwnerSpell(decorator.Get());
		}
		UKnockbackSpellDecorator* Build()
		{
			return decorator.Get();
		}
	};

	virtual void ProcessHit(AActor* hit, FVector location) override;

	virtual USpellBase* GetBaseSpell() override;
	virtual ISpell* GetOwnerSpell() override;
};
