// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidget_InGame.generated.h"

/**
 * 
 */
UCLASS()
class REFUGEE_API UUserWidget_InGame : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void UseCoin();

	void ShowNumImage(int Num);

	void ShowChaseImg();

	void HideChaseImg();
	
	void ShowReturnMessage();

	void UpdateCollectProgress(float CollectTime);

	void HideCollectProgress();

	void UpdateTime(int Time);

	void UpdateStamina(float StaminaValue);
	
private:
	void HideReturnMessage();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TArray<class UTexture2D*> ImageArray;

	UPROPERTY(meta = (BindWidget))
	class UImage* Count;

	UPROPERTY(meta = (BindWidget))
	class UImage* Coin;

	UPROPERTY(meta = (BindWidget))
	class UImage* Minute;

	UPROPERTY(meta = (BindWidget))
	class UImage* TenSecond;

	UPROPERTY(meta = (BindWidget))
	class UImage* Second;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* Stamina;

	UPROPERTY(meta = (BindWidget))
	class UWidget* ReturnMessage;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* CollectProgress;

	UPROPERTY()
	bool ShowCollectProgress = false;

	UPROPERTY(meta = (BindWidget))
	class UImage* Chase;

	FTimerHandle TimerHandle;
	
};
