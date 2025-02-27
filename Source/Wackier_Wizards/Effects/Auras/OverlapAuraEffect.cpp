// Fill out your copyright notice in the Description page of Project Settings.


#include "OverlapAuraEffect.h"
#include "Components/SphereComponent.h"
#include "../../Interfaces/Effectable.h"

void UOverlapAuraEffect::EndEffect()
{
	if (overlaps.Num() != 0)
	{
		for (TScriptInterface<IEffectable> target : overlaps)
		{
			ProcessEffectRemoval(target.GetInterface());
		}
	}

	UAuraEffect::EndEffect();
}

void UOverlapAuraEffect::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UAuraEffect::BeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (IEffectable* target = Cast<IEffectable>(OtherActor))
	{
		if (overlaps.Contains(target) == false)
		{
			ProcessEffect(target);
			overlaps.Add(target->_getUObject());
		}
	}
}

void UOverlapAuraEffect::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UAuraEffect::EndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	if (overlaps.Contains(OtherActor) == true)
	{
		ProcessEffectRemoval(Cast<IEffectable>(OtherActor));
		overlaps.Remove(OtherActor);
	}
}

void UOverlapAuraEffect::HandleOverlap()
{
	TArray<AActor*> current;
	aura->GetOverlappingActors(current);

	for (AActor* actor : current)
	{
		if (actor == owner.GetObject())
		{
			continue;
		}

		if (IEffectable* target = Cast<IEffectable>(actor))
		{
			if (overlaps.Contains(target) == false)
			{
				ProcessEffect(target);
				overlaps.Add(target->_getUObject());
			}
		}
	}
}
