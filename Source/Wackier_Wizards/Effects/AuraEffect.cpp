// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraEffect.h"
#include "Components/SphereComponent.h"
#include "../Components/EffectsComponent.h"
#include "../Interfaces/Effectable.h"
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
	aura->SetCollisionProfileName(FName("OverlapAll"));
	aura->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	aura->SetSphereRadius(effectData->auraSize);
	aura->SetHiddenInGame(false);
	aura->SetVisibility(true);

	aura->OnComponentBeginOverlap.AddDynamic(this, &UAuraEffect::BeginOverlap);
	aura->OnComponentEndOverlap.AddDynamic(this, &UAuraEffect::EndOverlap);

	niagara = UNiagaraFunctionLibrary::SpawnSystemAtLocation(actor->GetWorld(), effectData->effectNiagara, actor->GetActorLocation(), FRotator::ZeroRotator);
	niagara->AttachToComponent(actor->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	niagara->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	niagara->SetRelativeScale3D(FVector(effectData->auraSize / 20));

	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, FString::Printf(TEXT("Aura: %f"), aura->GetUnscaledSphereRadius()));
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, FString::Printf(TEXT("Niagra: %f"), niagara->GetRelativeScale3D().X));
}

void UAuraEffect::HandleOverlap()
{

}
