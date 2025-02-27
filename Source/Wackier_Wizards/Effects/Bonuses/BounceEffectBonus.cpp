// Fill out your copyright notice in the Description page of Project Settings.


#include "BounceEffectBonus.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../../Interfaces/Effectable.h"
#include "../EffectData.h"
#include "Wackier_Wizards/Definitions.h"

void UBounceEffectBonus::DoBonus()
{
	TArray<TEnumAsByte<EObjectTypeQuery>> types;
	types.Add(UEngineTypes::ConvertToObjectType(ECC_DamageableObject));
	types.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	TArray<TObjectPtr<AActor>> ignore;
	ignore.Add(effectOwner.Get());

	TArray<AActor*> targets;

	DrawDebugSphere(effectOwner->GetWorld(), effectOwner->GetActorLocation(), effectData->bonusRange, 12, FColor::Red, false, 0.3f);

	if (UKismetSystemLibrary::SphereOverlapActors(effectOwner->GetWorld(), effectOwner->GetActorLocation(), effectData->bonusRange, types, NULL, ignore, targets))
	{
		for (TObjectPtr<AActor> actor : targets)
		{
			if (IEffectable* effectable = Cast<IEffectable>(actor))
			{
				//If the target does not already contain this effect, apply the bounce effect (this will repeat until all nearby actors contain the effect).
				if (effectable->HasEffect(effectData->name) == false)
				{
					DrawDebugSphere(effectOwner->GetWorld(), effectOwner->GetActorLocation(), effectData->bonusRange, 12, FColor::Green, false, 0.5f);
					effectable->AddEffect(effectData);
				}
			}
		}
	}

	UBaseEffectBonus::DoBonus();
}
