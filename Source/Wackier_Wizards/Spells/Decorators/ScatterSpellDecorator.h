// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellDecorator.h"
#include "ScatterSpellDecorator.generated.h"

UCLASS()
class WACKIER_WIZARDS_API UScatterSpellDecorator : public USpellDecorator
{
	GENERATED_BODY()
	
//Scatter spell that fires projectiles or linetraces in random directions.
public:
	class WACKIER_WIZARDS_API Builder
	{
		TWeakObjectPtr<UScatterSpellDecorator> decorator;

	public:

		Builder(ISpell* data)
		{
			decorator = NewObject<UScatterSpellDecorator>();
			decorator->Decorate(data);
			data->SetOwnerSpell(decorator.Get());
		}
		ISpell* Build()
		{
			return decorator.Get();
		}
	};

	virtual bool CastSpell() override;
	virtual void ProcessHit(AActor* hit, FVector location) override;

	virtual USpellBase* GetBaseSpell() override;
};
