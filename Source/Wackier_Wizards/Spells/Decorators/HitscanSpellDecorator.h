// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellDecorator.h"
#include "HitscanSpellDecorator.generated.h"

class UNiagaraComponent;

UCLASS()
class WACKIER_WIZARDS_API UHitscanSpellDecorator : public USpellDecorator
{
	GENERATED_BODY()

public:
	class WACKIER_WIZARDS_API Builder
	{
		TWeakObjectPtr<UHitscanSpellDecorator> decorator;

	public:

		Builder(ISpell* data)
		{
			decorator = NewObject<UHitscanSpellDecorator>();
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
	virtual ISpell* GetOwnerSpell() override;
};
