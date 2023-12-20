// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_Negotiate.generated.h"

struct FBTNegotiateTaskMemory
{
	float RemainingNegotiateTime;
	bool showCoinEffect;
};

/**
 * 
 */
UCLASS()
class REFUGEE_API UBTTaskNode_Negotiate : public UBTTaskNode
{
	GENERATED_BODY()

	UBTTaskNode_Negotiate();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual uint16 GetInstanceMemorySize() const override;

public:
	UPROPERTY(Category = Wait, EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float NegotiateTime;

};
