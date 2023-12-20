// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "Character_Player.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnCollected);

/**
 * 
 */
UCLASS()
class REFUGEE_API ACharacter_Player : public ACharacter_Base
{
	GENERATED_BODY()
	
public:
	ACharacter_Player();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

	virtual void StartRun() override;

	virtual void EndRun() override;

	virtual void EndNegotiate() override;

	void StartNegotiate(FVector TargetLocation);

	float GetFwdBwdValue();

	void BeCaught();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void FwdBwd(float Value);

	void Yaw(float Value);

	bool IsRunning();

	void SetStamina(float Value);
	
	void StartCollect();

	void EndCollect();

	void Collected();

	void IgnoreInput(bool bIgnore);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float StaminaAdjustValue;

	UPROPERTY()
	class AGameModeBase_InGame* InGameGameMode;

	UPROPERTY()
	float FwdBwdValue = 0.f;

	UPROPERTY()
	float Stamina = 0.f;

	UPROPERTY()
	bool bRunActionCalled = false;

	UPROPERTY()
	bool bFoodBoxOverlapped = false;

	UPROPERTY()
	bool bCollecting = false;

	UPROPERTY()
	float CollectingTime = 0.f;

	UPROPERTY()
	FRotator NegotiationStartRot = FRotator::ZeroRotator;

	FOnCollected OnCollected;
};
