// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Catch.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character_Player.h"

EBTNodeResult::Type UBTTaskNode_Catch::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target")));
	if (IsValid(Target) == true)
	{
		ACharacter_Player* Player = Cast<ACharacter_Player>(Target);
		if (IsValid(Player) == true)
		{
			Player->BeCaught();
		}
		else
		{
			return EBTNodeResult::Failed;
		}
	}

	return Result;
}