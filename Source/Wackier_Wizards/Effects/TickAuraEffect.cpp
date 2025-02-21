// Fill out your copyright notice in the Description page of Project Settings.


#include "TickAuraEffect.h"
#include "Components/SphereComponent.h"
#include "../Interfaces/Effectable.h"

void UTickAuraEffect::Update(float deltaTime)
{
	UAuraEffect::Update(deltaTime);

	if (hasEnded == true || overlaps.Num() == 0)
	{
		return;
	}

	for (TScriptInterface<IEffectable> target : overlaps)
	{
		ProcessEffect(target.GetInterface());
	}

	if (_queue.Num() != 0)
	{
		EmptyQueue();
	}
}

void UTickAuraEffect::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UAuraEffect::BeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (IEffectable* target = Cast<IEffectable>(OtherActor))
	{
		if (overlaps.Contains(target) == false)
		{
			overlaps.Add(target->_getUObject());
		}
	}
}

void UTickAuraEffect::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UAuraEffect::EndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	if (IEffectable* target = Cast<IEffectable>(OtherActor))
	{
		QueueRemoval(target);
	}
}

void UTickAuraEffect::HandleOverlap()
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
				overlaps.Add(target->_getUObject());
			}
		}
	}
}

void UTickAuraEffect::QueueRemoval(IEffectable* target)
{
	if (overlaps.Contains(target) == true && _queue.Contains(target) == false)
	{
		_queue.Add(target->_getUObject());
	}
}

void UTickAuraEffect::EmptyQueue()
{
	for (TScriptInterface<IEffectable> target : _queue)
	{
		if (overlaps.Contains(target) == true)
		{
			overlaps.Remove(target);
		}
	}

	_queue.Empty();
}
