// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "UAnimInstance_Base.generated.h"

/**
 * 
 */
UCLASS()
class REFUGEE_API UAnimInstance_Base : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float Speed = 0.f;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool bIsRunning = false;

public:
	void StartRun();
	void EndRun();
	bool IsRunning();
};
