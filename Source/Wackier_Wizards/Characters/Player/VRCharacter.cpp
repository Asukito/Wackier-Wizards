// Fill out your copyright notice in the Description page of Project Settings.


#include "VRCharacter.h"

// Sets default values
AVRCharacter::AVRCharacter() : APlayerCharacter()
{
}

#pragma region "Helpers"
const FVector AVRCharacter::GetCastStartForward()
{
	return rightHandLocation;
}

#pragma endregion

