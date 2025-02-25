


#include "ResultantEffectContainer.h"
#include "ResultantEffectObject.h"
#include "ResultantEffectData.h"
#include "../EffectData.h"

// Sets default values
AResultantEffectContainer::AResultantEffectContainer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

UEffectData* AResultantEffectContainer::CheckIfValid(FString nameOne, FString nameTwo)
{
	if (_resultantObjects.Num() == 0)
	{
		return nullptr;
	}

	for (TObjectPtr<UResultantEffectObject> object : _resultantObjects)
	{
		if (TObjectPtr<UEffectData> effect = object->CheckIfValid(nameOne, nameTwo))
		{
			return effect;
		}
	}

	return nullptr;
}

// Called when the game starts or when spawned
void AResultantEffectContainer::BeginPlay()
{
	Super::BeginPlay();
	
	for (TObjectPtr<UResultantEffectData> effect : _resultantEffects)
	{
		TObjectPtr<UResultantEffectObject> object = NewObject<UResultantEffectObject>();
		object->Init(effect);
		_resultantObjects.Add(object);
	}
}



