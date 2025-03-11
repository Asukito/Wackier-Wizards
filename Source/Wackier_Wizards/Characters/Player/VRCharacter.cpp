// Fill out your copyright notice in the Description page of Project Settings.


#include "VRCharacter.h"
#include "Components/WidgetComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AVRCharacter::AVRCharacter() : APlayerCharacter()
{
	widgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Component"));
	checkf(widgetComponent, TEXT("VR Character failed to initialise WidgetComponent"));
	widgetComponent->SetupAttachment(GetCamera());
	widgetComponent->SetRelativeLocation(FVector(100, 0, 0));
	widgetComponent->SetRelativeRotation(FRotator(0, 180, 0));
	widgetComponent->SetDrawSize(FVector2D(1920, 1080));
}

#pragma region "Helpers"
const FVector AVRCharacter::GetCastStartForward()
{
	// Get the forward vector from the right hand's rotation
	return rightHandRotation.Vector();
}

#pragma endregion

