// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellDecorator.h"
#include "AOESpellDecorator.generated.h"

/**
 * 
 */
UCLASS()
class WACKIER_WIZARDS_API UAOESpellDecorator : public USpellDecorator
{
	GENERATED_BODY()
	
public:
	class WACKIER_WIZARDS_API Builder
	{
		TWeakObjectPtr<UAOESpellDecorator> decorator;

	public:

		Builder(ISpell* data)
		{
			decorator = NewObject<UAOESpellDecorator>();
			decorator->Decorate(data);
			data->SetOwnerSpell(decorator.Get());
		}
		ISpell* Build()
		{
			return decorator.Get();
		}
	};

	virtual bool CastSpell() override;
	void ProcessHit(AActor* hit, FVector location) override;
};
