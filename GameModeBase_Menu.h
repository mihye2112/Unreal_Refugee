// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeBase_Menu.generated.h"

/**
 * 
 */
UCLASS()
class REFUGEE_API AGameModeBase_Menu : public AGameModeBase
{
	GENERATED_BODY()

	AGameModeBase_Menu();
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UUserWidget* MainUserWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TSubclassOf<UUserWidget> UserWidget;

	UPROPERTY()
	class UAudioComponent* AudioComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class USoundBase* BGMSound;
};
