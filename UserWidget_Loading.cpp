// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget_Loading.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstance_Base.h"

void UUserWidget_Loading::NativeConstruct()
{
	Super::NativeConstruct();

	ShowImage();
}

void UUserWidget_Loading::ShowImage()
{
	GetWorld()->GetTimerManager().ClearTimer(TimeHandle);

	if (ImageIndex < ImageArray.Num())
	{
		Image->SetBrushResourceObject(ImageArray[ImageIndex]);

		ImageIndex++;

		GetWorld()->GetTimerManager().SetTimer(TimeHandle, this, &UUserWidget_Loading::ShowImage, 3.0f);
	}
	else
	{
		UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
		if (IsValid(GameInstance))
		{
			UGameInstance_Base* GameInstanceBsse = Cast<UGameInstance_Base>(GameInstance);
			if (IsValid(GameInstanceBsse))
			{
				GameInstanceBsse->HideLoadingWidget();
			}
		}
	}
}