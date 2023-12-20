// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance_Base.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

UGameInstance_Base::UGameInstance_Base()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> Widget(TEXT("WidgetBlueprint'/Game/UI/Loading_WB.Loading_WB_C'"));
	if (Widget.Succeeded() == true)
	{
		LoadingWidgetClass = Widget.Class;
	}
}

void UGameInstance_Base::ShowLoadingWidget()
{
	if (IsValid(LoadingWidget) == false)
	{
		LoadingWidget = CreateWidget(GetWorld(), LoadingWidgetClass);
	}

	if (IsValid(LoadingWidget) == true)
	{
		GetWorld()->GetGameViewport()->RemoveAllViewportWidgets();
		LoadingWidget->AddToViewport();
	}
}

void UGameInstance_Base::HideLoadingWidget()
{
	if (OpenLevelName != NAME_None)
	{
		UGameplayStatics::OpenLevel(this, OpenLevelName);
		OpenLevelName = NAME_None;
	}
	else
	{
		if (IsValid(LoadingWidget) == true)
		{
			LoadingWidget->RemoveFromViewport();
		}
	}
}

void UGameInstance_Base::OpenLevel(FName LevelName, bool showLoadingWidget)
{
	if (showLoadingWidget == true)
	{
		OpenLevelName = LevelName;
		ShowLoadingWidget();
	}
	else
	{
		UGameplayStatics::OpenLevel(this, LevelName);
	}
}