// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EnemyType.h"
#include "EnemyFactory.generated.h"

class ABaseEnemy;

UCLASS()
class WACKIER_WIZARDS_API UEnemyFactory : public UObject
{
	GENERATED_BODY()
	
public:
	ABaseEnemy* CreateEnemy(EnemyType type);
};
