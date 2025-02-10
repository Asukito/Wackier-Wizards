// Fill out your copyright notice in the Description page of Project Settings.


#include "AOEEffectBonus.h"
#include "../Objects/AOEActor.h"
#include "EffectData.h"

void UAOEEffectBonus::DoBonus()
{
	TObjectPtr<AAOEActor> actor = effectOwner->GetWorld()->SpawnActor<AAOEActor>(AAOEActor::StaticClass(), effectOwner->GetActorLocation(), FRotator::ZeroRotator);

	actor->Init(effectData);
}
