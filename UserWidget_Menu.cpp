// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget_Menu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstance_Base.h"

void UUserWidget_Menu::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartButton != nullptr)
	{
		StartButton->OnClicked.AddDynamic(this, &UUserWidget_Menu::Start);
	}

	if (ExitButton != nullptr)
	{
		ExitButton->OnClicked.AddDynamic(this, &UUserWidget_Menu::Exit);
	}
}

void UUserWidget_Menu::Start()
{
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	if (IsValid(GameInstance))
	{
		UGameInstance_Base* GameInstanceBase = Cast<UGameInstance_Base>(GameInstance);
		if (IsValid(GameInstanceBase))
		{
			GameInstanceBase->OpenLevel(TEXT("InGame"), ShowLoading);
		}
	}

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (IsValid(Controller) == true)
	{
		Controller->SetShowMouseCursor(false);
	}
}

void UUserWidget_Menu::Exit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}