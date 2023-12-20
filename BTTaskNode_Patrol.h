// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_Patrol.generated.h"

/**
 * 
 */
UCLASS()
class REFUGEE_API UBTTaskNode_Patrol : public UBTTaskNode
{
	GENERATED_BODY()

	UBTTaskNode_Patrol();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
