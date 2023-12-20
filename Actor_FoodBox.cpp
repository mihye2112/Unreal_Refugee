// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_FoodBox.h"
#include "Components/BoxComponent.h"
#include "Character_Player.h"
#include "Kismet/GameplayStatics.h"
#include "GameModeBase_InGame.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AActor_FoodBox::AActor_FoodBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AActor_FoodBox::BeginPlay()
{
	Super::BeginPlay();

	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld());
	if (IsValid(GameMode) == true)
	{
		AGameModeBase_InGame* InGameGameMode = Cast<AGameModeBase_InGame>(GameMode);
		if (IsValid(InGameGameMode) == true)
		{
			FoodEffect = InGameGameMode->SpawnBoxEffect(GetActorLocation());
		}
	}
}

bool AActor_FoodBox::CanCollect()
{
	return !bCollected;
}

void AActor_FoodBox::Collected()
{
	bCollected = true;

	if (FoodEffect != nullptr)
	{
		FoodEffect->DestroyComponent();
	}
}

