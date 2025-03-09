// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UObject/ObjectMacros.h"
#include "UIManagerSubsystem.generated.h"

UENUM(BlueprintType)
enum class EWidgetType : uint8
{
	PLAYER_HUD,
	GRIMOIRE,
	QUICK_SELECT,
	PAUSE_MENU,
	OPTIONS,
	STAGE_COMPLETE
};

class UGrimoireWidget;
class UPauseMenuWidget;
class UOptionsWidget;
class UStageCompleteWidget;
class UQuickSelectWidget;

UCLASS(Blueprintable)
class WACKIER_WIZARDS_API UUIManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	void CreateWidgets(APlayerController* controller);

	void ToggleWidget(EWidgetType target, APlayerController* controller);
	void AddToViewport(EWidgetType target, APlayerController* controller);
	void RemoveFromViewport(EWidgetType target, APlayerController* controller);

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

private:
	void AddGrimoireToViewport(APlayerController* controller);

	void AddQuickSelectToViewport(APlayerController* controller);

	void AddPauseMenuToViewport(APlayerController* controller);
	void RemovePauseMenuFromViewport(APlayerController* controller);

	void AddOptionsToViewport(APlayerController* controller);
	void RemoveOptionsFromViewport(APlayerController* controller);

	void AddStageCompleteToViewport(APlayerController* controller);

	void ClearViewport(APlayerController* controller);
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGrimoireWidget> _grimoireDefault;
	UPROPERTY()
	TObjectPtr<UGrimoireWidget> _grimoire;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UQuickSelectWidget> _quickSelectDefault;
	UPROPERTY()
	TObjectPtr<UQuickSelectWidget> _quickSelect;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPauseMenuWidget> _pauseMenuDefault;
	UPROPERTY()
	TObjectPtr<UPauseMenuWidget> _pauseMenu;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UOptionsWidget> _optionsMenuDefault;
	UPROPERTY()
	TObjectPtr<UOptionsWidget> _optionsMenu;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UStageCompleteWidget> _stageCompleteDefault;
	UPROPERTY()
	TObjectPtr<UStageCompleteWidget> _stageCompleteWidget;

	UPROPERTY()
	TMap<EWidgetType, TObjectPtr<UUserWidget>> _widgets;

	TMap<EWidgetType, TFunction<void(UUIManagerSubsystem*, APlayerController*)>> _addToViewportFunctions;
	TMap<EWidgetType, TFunction<void(UUIManagerSubsystem*, APlayerController*)>> _removeFromViewportFunctions;

	bool _isLoaded;
};
