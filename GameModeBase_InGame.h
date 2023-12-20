// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeBase_InGame.generated.h"

/**
 * 
 */
UCLASS()
class REFUGEE_API AGameModeBase_InGame : public AGameModeBase
{
	GENERATED_BODY()

	AGameModeBase_InGame();

public:
	const static int CoinCount = 1;
	const static int CollectMaxCount = 6;
	const static int PlayTime = 300;
	const static int CountTime = 10;
	const static int MaxStamina = 100;

	const static float CollectTime;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UParticleSystemComponent* SpawnBoxEffect(FVector Location);
	void SpawnReturnPosEffect(FVector Location);
	void NegotiateEffect(FVector Location);
	void UpdateStamina(float StaminaValue);
	void AddChasingEnemy(class ACharacter_Enemy*);
	void RemoveChasingEnemy(class ACharacter_Enemy*);
	void UseCoin();
	void Collecting(float Time);
	void EndCollect();
	void Collect();
	void SpawnReturnPos();
	void GameClear();
	void GameOver();
	void TimeOver();
	bool CanNegotiate();
	void EndNegotiate();

private:
	UPROPERTY()
	float PlayRemainTime = 0.f;;

	UPROPERTY()
	FVector ReturnPos;

	UPROPERTY()
	int CollectCount = 0;

	UPROPERTY()
	int RemainCoinCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TSubclassOf<UUserWidget> UserWidget;
	UPROPERTY()
	class UUserWidget_InGame* InGameWidget;

	UPROPERTY()
	TArray<class ACharacter_Enemy*> ChasingEnemyArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UParticleSystem* BoxParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UParticleSystem* ReturnPosParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UParticleSystem* CoinParticle;

	UPROPERTY()
	class UAudioComponent* BGMAudioComponent; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class USoundBase* StartBGMSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class USoundBase* BGMSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class USoundBase* ChaseBGMSound;

	UPROPERTY()
	class UAudioComponent* SEAudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class USoundBase* NegotiateSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class USoundBase* AlertSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class USoundBase* ExhaustedSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class USoundBase* CountTimeSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class USoundBase* FoodSound;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool bCanReturn = false;

private:
	UFUNCTION(BlueprintCallable)
	void PlayBGM(class USoundBase* Sound);

	void PlaySE(bool play, class USoundBase* Sound = nullptr);
};
