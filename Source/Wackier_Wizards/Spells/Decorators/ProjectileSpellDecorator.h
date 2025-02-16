// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellDecorator.h"
#include "ProjectileSpellDecorator.generated.h"

class USpellBase;

UCLASS()
class WACKIER_WIZARDS_API UProjectileSpellDecorator : public USpellDecorator
{
	GENERATED_BODY()
	
public:
	class WACKIER_WIZARDS_API Builder
	{
		TWeakObjectPtr<UProjectileSpellDecorator> decorator;

	public:

		Builder(ISpell* data)
		{
			decorator = NewObject<UProjectileSpellDecorator>();
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
