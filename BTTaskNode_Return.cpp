// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Return.h"
#include "AIController.h"
#include "Character_Enemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTaskNode_Return::UBTTaskNode_Return()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTaskNode_Return::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (IsValid(Pawn) == true)
	{
		ACharacter_Enemy* Character = Cast<ACharacter_Enemy>(Pawn);
		if (IsValid(Character) == true)
		{
			Character->EndRun();
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(Character->Controller, Character->GetStartPos());

			return EBTNodeResult::InProgress;
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

void UBTTaskNode_Return::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (IsValid(Pawn) == true)
	{
		ACharacter_Enemy* Character = Cast<ACharacter_Enemy>(Pawn);
		if (IsValid(Character) == true && FVector::Dist(Character->GetStartPos(), Character->GetActorLocation()) < 50.f)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), nullptr);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}

}