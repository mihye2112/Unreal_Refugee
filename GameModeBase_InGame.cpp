// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeBase_InGame.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Character_Enemy.h"
#include "Character_Player.h"
#include "Actor_ReturnPos.h"
#include "UserWidget_InGame.h"
#include "Particles/ParticleSystem.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "Engine/Level.h"

const float AGameModeBase_InGame::CollectTime = 2.6f;

AGameModeBase_InGame::AGameModeBase_InGame()
{
	PrimaryActorTick.bCanEverTick = true;

	BGMAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BGMAudio"));
	SEAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SEAudio"));

}

void AGameModeBase_InGame::BeginPlay()
{
	APawn* Pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (IsValid(Pawn) == true)
	{
		FVector Pos = Pawn->GetActorLocation();
		Pos.Z = -10.f;
		ReturnPos = Pos;
	}

	if (IsValid(UserWidget) == true)
	{
		UUserWidget* Widget = CreateWidget(GetWorld(), UserWidget);
		if (IsValid(Widget) == true)
		{
			InGameWidget = Cast<UUserWidget_InGame>(Widget);

			if (IsValid(InGameWidget) == true)
			{
				InGameWidget->AddToViewport();
			}
		}
	}	

	PlayBGM(StartBGMSound);

	PlayRemainTime = AGameModeBase_InGame::PlayTime;

	RemainCoinCount = AGameModeBase_InGame::CoinCount;
}

void AGameModeBase_InGame::Tick(float DeltaTime)
{
	PlayRemainTime -= DeltaTime;

	if (PlayRemainTime <= 0.f)
	{
		TimeOver();
		return;
	}

	if (FMath::IsNearlyEqual(PlayRemainTime, CountTime) == true)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), CountTimeSound);
	}

	if (IsValid(InGameWidget) == true)
	{
		InGameWidget->UpdateTime(PlayRemainTime);
	}
}

UParticleSystemComponent* AGameModeBase_InGame::SpawnBoxEffect(FVector Location)
{
	return UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BoxParticle, Location, FRotator::ZeroRotator, FVector(1.f));
}

void AGameModeBase_InGame::NegotiateEffect(FVector Location)
{
	UGameplayStatics::PlaySound2D(GetWorld(), NegotiateSound);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), CoinParticle, Location, FRotator::ZeroRotator, FVector(1.f));
}

void AGameModeBase_InGame::SpawnReturnPosEffect(FVector Location)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ReturnPosParticle, Location, FRotator::ZeroRotator, FVector(1.f));
}

void AGameModeBase_InGame::UpdateStamina(float StaminaValue)
{
	if (FMath::IsNearlyZero(StaminaValue) == true)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), ExhaustedSound);
	}

	if (IsValid(InGameWidget) == true)
	{
		InGameWidget->UpdateStamina(StaminaValue);
	}
}

void AGameModeBase_InGame::AddChasingEnemy(ACharacter_Enemy* Enemy)
{
	if (ChasingEnemyArray.Contains(Enemy) == false)
	{
		if (ChasingEnemyArray.Num() == 0)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), AlertSound);
			PlayBGM(ChaseBGMSound);

			if (IsValid(InGameWidget) == true)
			{
				InGameWidget->ShowChaseImg();
			}
		}

		ChasingEnemyArray.Add(Enemy);
	}
}

void AGameModeBase_InGame::RemoveChasingEnemy(ACharacter_Enemy* Enemy)
{
	if (ChasingEnemyArray.Contains(Enemy) == true)
	{
		ChasingEnemyArray.Remove(Enemy);

		if (ChasingEnemyArray.Num() == 0)
		{
			PlayBGM(BGMSound);

			if (IsValid(InGameWidget) == true)
			{
				InGameWidget->HideChaseImg();
			}
		}
	}
}

void AGameModeBase_InGame::UseCoin()
{
	if (IsValid(InGameWidget) == true)
	{
		InGameWidget->UseCoin();
	}
}

void AGameModeBase_InGame::Collecting(float Time)
{
	if (FMath::IsNearlyZero(Time) == true)
	{
		PlaySE(true, FoodSound);
	}

	if (IsValid(InGameWidget) == true)
	{
		InGameWidget->UpdateCollectProgress(Time);
	}	
}

void AGameModeBase_InGame::EndCollect()
{
	if (IsValid(InGameWidget) == true)
	{
		InGameWidget->HideCollectProgress();
	}

	PlaySE(false);
}

void AGameModeBase_InGame::Collect()
{
	CollectCount++;

	if (IsValid(InGameWidget) == true)
	{
		InGameWidget->ShowNumImage(CollectCount);
	}

	if (CollectCount == AGameModeBase_InGame::CollectMaxCount)
	{
		bCanReturn = true;
		SpawnReturnPos();

		if (IsValid(InGameWidget) == true)
		{
			InGameWidget->ShowReturnMessage();
		}
	}	
}

void AGameModeBase_InGame::SpawnReturnPos()
{
	FVector SpawnLocation = ReturnPos;
	FActorSpawnParameters SpawnPrams;
	GetWorld()->SpawnActor<AActor>(AActor_ReturnPos::StaticClass(), SpawnLocation, FRotator::ZeroRotator, SpawnPrams);
}

void AGameModeBase_InGame::GameClear()
{
	UGameplayStatics::OpenLevel(this, TEXT("GameClear"));
}

void AGameModeBase_InGame::GameOver()
{
	UGameplayStatics::OpenLevel(this, TEXT("GameOver"));
}

void AGameModeBase_InGame::TimeOver()
{
	UGameplayStatics::OpenLevel(this, TEXT("TimeOver"));
}

bool AGameModeBase_InGame::CanNegotiate()
{
	return RemainCoinCount > 0;
}

void AGameModeBase_InGame::EndNegotiate()
{
	RemainCoinCount--;

	APawn* Pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (IsValid(Pawn) == true)
	{
		ACharacter_Player* Player = Cast<ACharacter_Player>(Pawn);
		if (IsValid(Player) == true)
		{
			Player->EndNegotiate();
		}
	}
}

void AGameModeBase_InGame::PlayBGM(class USoundBase* Sound)
{
	if (IsValid(BGMAudioComponent))
	{
		BGMAudioComponent->SetSound(Sound);
		BGMAudioComponent->Play();
	}
}

void AGameModeBase_InGame::PlaySE(bool play, class USoundBase* Sound)
{
	if (IsValid(SEAudioComponent))
	{
		if (play == true)
		{
			SEAudioComponent->SetSound(Sound);
			SEAudioComponent->Play();
		}
		else
		{
			SEAudioComponent->Stop();
		}
	}
}