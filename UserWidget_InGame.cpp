// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget_InGame.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "GameModeBase_InGame.h"

void UUserWidget_InGame::NativeConstruct()
{
	Super::NativeConstruct();

	ShowNumImage(0);
	HideReturnMessage();
	HideCollectProgress();
	HideChaseImg();
}

void UUserWidget_InGame::UseCoin()
{
	Coin->SetVisibility(ESlateVisibility::Hidden);
}

void UUserWidget_InGame::ShowNumImage(int Num)
{
	if (Num < ImageArray.Num())
	{
		Count->SetBrushResourceObject(ImageArray[Num]);
	}
}

void UUserWidget_InGame::ShowChaseImg()
{
	Chase->SetVisibility(ESlateVisibility::Visible);
}

void UUserWidget_InGame::HideChaseImg()
{
	Chase->SetVisibility(ESlateVisibility::Hidden);
}

void UUserWidget_InGame::ShowReturnMessage()
{
	ReturnMessage->SetVisibility(ESlateVisibility::HitTestInvisible);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UUserWidget_InGame::HideReturnMessage, 2.f);
}

void UUserWidget_InGame::HideReturnMessage()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	ReturnMessage->SetVisibility(ESlateVisibility::Hidden);
}

void UUserWidget_InGame::UpdateCollectProgress(float CollectTime)
{
	if (ShowCollectProgress == false)
	{
		ShowCollectProgress = true;
		CollectProgress->SetVisibility(ESlateVisibility::HitTestInvisible);
	}

	float Percent = CollectTime / AGameModeBase_InGame::CollectTime;
	CollectProgress->SetPercent(Percent);
}

void UUserWidget_InGame::HideCollectProgress()
{
	ShowCollectProgress = false;
	CollectProgress->SetVisibility(ESlateVisibility::Hidden);
}

void UUserWidget_InGame::UpdateTime(int Time)
{
	int MinuteTime = Time / 60;
	if (MinuteTime < ImageArray.Num())
	{
		Minute->SetBrushResourceObject(ImageArray[MinuteTime]);
	}

	int RemainSecond = Time - (MinuteTime * 60);
	int TenSecondTime = RemainSecond / 10;
	if (TenSecondTime < ImageArray.Num())
	{
		TenSecond->SetBrushResourceObject(ImageArray[TenSecondTime]);
	}

	int SecondTime = RemainSecond % 10;
	if (SecondTime < ImageArray.Num())
	{
		Second->SetBrushResourceObject(ImageArray[SecondTime]);
	}

}

void UUserWidget_InGame::UpdateStamina(float StaminaValue)
{
	float percent = StaminaValue / AGameModeBase_InGame::MaxStamina;
	Stamina->SetPercent(percent);
}