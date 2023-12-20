// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidget_Menu.generated.h"

/**
 * 
 */
UCLASS()
class REFUGEE_API UUserWidget_Menu : public UUserWidget
{
	GENERATED_BODY()


public:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* StartButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ExitButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool ShowLoading;

private:
	UFUNCTION()
	void Start();

	UFUNCTION()
	void Exit();
};
