// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_Enemy.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"

AAIController_Enemy::AAIController_Enemy()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BD(TEXT("BlackboardData'/Game/AI/Enemy_BB.Enemy_BB'"));
	if (BD.Succeeded() == true)
	{
		BlackboardData = BD.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("BehaviorTree'/Game/AI/Enemy_BT.Enemy_BT'"));
	if (BT.Succeeded() == true)
	{
		BehaviorTree = BT.Object;
	}
}

void AAIController_Enemy::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BlackboardData, Blackboard) == true)
	{
		if (RunBehaviorTree(BehaviorTree) == true)
		{

		}
	}
}

void AAIController_Enemy::OnUnPossess()
{
	Super::OnUnPossess();
}