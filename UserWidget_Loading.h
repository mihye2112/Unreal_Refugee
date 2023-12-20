// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidget_Loading.generated.h"

/**
 * 
 */
UCLASS()
class REFUGEE_API UUserWidget_Loading : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
private:
	void ShowImage();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TArray<class UTexture2D*> ImageArray;
	UPROPERTY(meta = (BindWidget))
	class UImage* Image;
	UPROPERTY()
	int ImageIndex = 0;

	FTimerHandle TimeHandle;

};
