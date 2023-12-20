// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_FindPatrolPos.h"
#include "NavigationSystem.h"
#include "AIController.h"
#include "Character_Enemy.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTaskNode_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	UNavigationSystemV1* NaviSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (IsValid(NaviSystem) == true)
	{
		APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
		if (IsValid(Pawn) == true)
		{
			ACharacter_Enemy* Character = Cast<ACharacter_Enemy>(Pawn);
			if (IsValid(Character) == true)
			{
				FNavLocation RandomLocation;
				bool bResult = NaviSystem->GetRandomPointInNavigableRadius(Character->GetStartPos(), Character->GetPatrolRadius(), RandomLocation);

				if (bResult == true)
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("PatrolPos")), RandomLocation.Location);
				}
				else
				{
					return EBTNodeResult::Failed;
				}
			}
			else
			{
				return EBTNodeResult::Failed;
			}
		}
		else
		{
			return EBTNodeResult::Failed;
		}
	}
	else
	{
		return EBTNodeResult::Failed;
	}


	return Result;
}
