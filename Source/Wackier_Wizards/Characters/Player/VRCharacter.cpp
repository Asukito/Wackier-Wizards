// Fill out your copyright notice in the Description page of Project Settings.


#include "VRCharacter.h"

// Sets default values
AVRCharacter::AVRCharacter() : APlayerCharacter()
{
}

#pragma region "Helpers"
const FVector AVRCharacter::GetCastStartForward()
{
	// Get the forward vector from the right hand's rotation
	return rightHandRotation.Vector();
}

#pragma endregion

