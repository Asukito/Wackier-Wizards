// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraEffect.h"
#include "Components/SphereComponent.h"
#include "../../Components/EffectsComponent.h"
#include "../../Interfaces/Effectable.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

void UAuraEffect::StartEffect(UEffectData* data, AActor* actor, UEffectsComponent* list)
{
	hasEnded = false;
	//Bind the EffectsComponent QueueRemoval function to clearDelegate;
	_clearDelegate.BindUObject(list, &UEffectsComponent::QueueRemoval);

	//Checks that the target is effectable and contains a reference if true. If not, clear the effect.
	if (IEffectable* target = Cast<IEffectable>(actor))
	{
		owner = target->_getUObject();
	}
	else
	{
		ClearEffect();
		return;
	}

	effectData = data;
	duration = effectData->duration;

	SetUpAura(actor);

	if (aura == nullptr)
	{
		return;
	}

	HandleOverlap();
}

void UAuraEffect::Update(float deltaTime)
{
	UBaseEffect::Update(deltaTime);

	if (hasEnded == true)
	{
		return;
	}

	if (timer >= duration)
	{
		EndEffect();
		return;
	}
}

void UAuraEffect::EndEffect()
{
	if (niagara != nullptr)
	{
		niagara->DestroyComponent();
	}

	aura->DestroyComponent();
	overlaps.Empty();

	UBaseEffect::EndEffect();
}

void UAuraEffect::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == owner.GetObject())
	{
		return;
	}
}

void UAuraEffect::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == owner.GetObject())
	{
		return;
	}
}

void UAuraEffect::SetUpAura(AActor* actor)
{
	aura = NewObject<USphereComponent>(actor->GetRootComponent(), TEXT("AURA"));
	aura->RegisterComponent();

	aura->AttachToComponent(actor->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	float originalRadius = aura->GetUnscaledSphereRadius();

	if (effectData->type == EffectType::SHIELD)
	{
		aura->SetCollisionProfileName(FName("Shield"));
	}
	else
	{
		aura->SetCollisionProfileName(FName("Aura"));
	}

	aura->SetSphereRadius(effectData->auraSize);
	aura->SetHiddenInGame(false);
	aura->SetVisibility(true);

	aura->OnComponentBeginOverlap.AddDynamic(this, &UAuraEffect::BeginOverlap);
	aura->OnComponentEndOverlap.AddDynamic(this, &UAuraEffect::EndOverlap);

	FVector location = actor->GetActorLocation();
	FRotator rotation = actor->GetActorRotation();

	niagara = UNiagaraFunctionLibrary::SpawnSystemAttached(effectData->effectNiagara, actor->GetRootComponent(), "", location, rotation, EAttachLocation::KeepWorldPosition, true, true, ENCPoolMethod::AutoRelease, true);
	niagara->SetRelativeScale3D(FVector((effectData->auraSize / 50) * 0.75));
}

void UAuraEffect::HandleOverlap()
{

}
