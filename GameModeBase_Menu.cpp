// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeBase_Menu.h"
#include "BluePrint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"

AGameModeBase_Menu::AGameModeBase_Menu()
{
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
}

void AGameModeBase_Menu::BeginPlay()
{
	if (IsValid(UserWidget) == true)
	{
		MainUserWidget = CreateWidget(GetWorld(), UserWidget);

		if (MainUserWidget != nullptr)
		{
			MainUserWidget->AddToViewport();
		}
	}

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (IsValid(Controller) == true)
	{
		Controller->SetShowMouseCursor(true);
	}

	if (IsValid(AudioComponent))
	{
		AudioComponent->SetSound(BGMSound);
		AudioComponent->Play();
	}
}
