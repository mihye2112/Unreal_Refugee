// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstanceBase.h"
#include "AnimInstance_Player.generated.h"

/**
 * 
 */
UCLASS()
class REFUGEE_API UAnimInstance_Player : public UAnimInstanceBase
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float FwdBwdValue = 0.f;
};
