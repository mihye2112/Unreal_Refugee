// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameInstance_Base.generated.h"

/**
 * 
 */
UCLASS()
class REFUGEE_API UGameInstance_Base : public UGameInstance
{
	GENERATED_BODY()
	
	UGameInstance_Base();

public:
	void ShowLoadingWidget();
	void HideLoadingWidget();
	void OpenLevel(FName LevelName, bool showLoadingWidget);

private:
	UPROPERTY()
	TSubclassOf<UUserWidget> LoadingWidgetClass;
	UPROPERTY()
	UUserWidget* LoadingWidget;
	UPROPERTY()
	FName OpenLevelName = NAME_None;
};
