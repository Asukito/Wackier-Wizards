// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellFactory.h"
#include "SpellIncludes.h"

USpellBase* USpellFactory::CreateSpell(USpellData* spellData, ISpellCaster* owner)
{
	TObjectPtr<USpellBase> spell = nullptr;

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

		case SpellType::PROJECTILE:
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, FString::Printf(TEXT("Created %s"), *spellData->name));
			spell = NewObject<UProjectileSpell>();
			spell->Init(spellData, owner);

			return spell;

		case SpellType::PROJECTILE_AOE:
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, FString::Printf(TEXT("Created %s"), *spellData->name));
			spell = NewObject<UAOEProjectileSpell>();
			spell->Init(spellData, owner);

			return spell;

		case SpellType::LOCAL_AOE:
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, FString::Printf(TEXT("Created %s"), *spellData->name));
			spell = NewObject<ULocalAOESpell>();
			spell->Init(spellData, owner);

			return spell;

		case SpellType::HITSCAN_AOE:
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, FString::Printf(TEXT("Created %s"), *spellData->name));
			spell = NewObject<UAOEHitscanSpell>();
			spell->Init(spellData, owner);

			return spell;

		case SpellType::TRAIL_PROJECTILE_AOE:
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, FString::Printf(TEXT("Created %s"), *spellData->name));
			spell = NewObject<UTrailAOEProjectileSpell>();
			spell->Init(spellData, owner);

			return spell;
	}

	return nullptr;
}


