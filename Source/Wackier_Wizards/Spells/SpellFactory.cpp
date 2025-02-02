// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellFactory.h"
#include "SpellBase.h"
#include "SpellData.h"
#include "SpellType.h"
#include "HitscanSpell.h"
#include "SelfSpell.h"	

USpellBase* USpellFactory::CreateSpell(USpellData* spellData, ISpellCaster* owner)
{
	USpellBase* spell = nullptr;

	switch (spellData->type)
	{
		case SpellType::HITSCAN:
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, FString::Printf(TEXT("Created %s"), *spellData->name));
			spell = NewObject<UHitscanSpell>();
			spell->Init(spellData, owner);

			return spell;

		case SpellType::SELF:
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, FString::Printf(TEXT("Created %s"), *spellData->name));			
			spell = NewObject<USelfSpell>();
			spell->Init(spellData, owner);

			return spell;
	}

	return nullptr;
}


