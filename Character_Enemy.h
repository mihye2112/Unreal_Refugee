// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "Character_Enemy.generated.h"

UCLASS()
class REFUGEE_API ACharacter_Enemy : public ACharacter_Base
{
	GENERATED_BODY()

public:
	ACharacter_Enemy();

protected:
	virtual void BeginPlay() override;


public:
	FVector GetStartPos();
	float GetPatrolRadius();
	bool IsNegotiating();
	bool IsNegotiated();

	virtual void EndNegotiate() override;

private:
	UPROPERTY()
	FVector StartPos = FVector::ZeroVector;
	UPROPERTY()
	bool bIsNegotiated = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float PatrolRadius = 500.0f;
};
