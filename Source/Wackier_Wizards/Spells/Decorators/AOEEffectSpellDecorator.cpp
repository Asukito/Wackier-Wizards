// Fill out your copyright notice in the Description page of Project Settings.


#include "AOEEffectSpellDecorator.h"
#include "../../Objects/AOEEffectActor.h"
#include "../../Interfaces/SpellCaster.h"
#include "../SpellData.h"

void UAOEEffectSpellDecorator::ProcessHit(AActor* hit, FVector location, int damageAdjustment)
{
	spell->ProcessHit(hit, location, damageAdjustment);

	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	TObjectPtr<AAOEEffectActor> actor = spellOwner->GetSpellOwner()->GetWorld()->SpawnActor<AAOEEffectActor>(AAOEEffectActor::StaticClass(), location, FRotator::ZeroRotator, params);
	actor->AddIgnoredActor(spellOwner->GetSpellOwner());

	actor->Init(spellData->aoeEffect, spellData->aoeEffectDuration, spellData->aoeEffectSize, spellData->doPullEffect);
}
