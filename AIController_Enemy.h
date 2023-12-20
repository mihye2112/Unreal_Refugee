// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIController_Enemy.generated.h"

/**
 * 
 */
UCLASS()
class REFUGEE_API AAIController_Enemy : public AAIController
{
	GENERATED_BODY()
	
	AAIController_Enemy();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:
	class UBlackboardData* BlackboardData;
	class UBehaviorTree* BehaviorTree;

};
