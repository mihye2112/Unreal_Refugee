// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Wait.h"
#include "AIController.h"
#include "Character_Enemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

UBTTaskNode_Wait::UBTTaskNode_Wait()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTaskNode_Wait::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	FBTWaitTaskMemory* MyMemory = (FBTWaitTaskMemory*)NodeMemory;
	MyMemory->RemainingWaitTime = FMath::FRandRange(FMath::Max(1.0f, WaitTime - RandomDeviation), (WaitTime + RandomDeviation));

	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (IsValid(Pawn) == true)
	{
		ACharacter_Enemy* Character = Cast<ACharacter_Enemy>(Pawn);
		if (IsValid(Character) == true)
		{
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

void UBTTaskNode_Wait::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	FBTWaitTaskMemory* MyMemory = (FBTWaitTaskMemory*)NodeMemory;
	MyMemory->RemainingWaitTime -= DeltaSeconds;

	if (MyMemory->RemainingWaitTime <= 0.0f)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target")));
	if (IsValid(Target) == true)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

}

uint16 UBTTaskNode_Wait::GetInstanceMemorySize() const
{
	return sizeof(FBTWaitTaskMemory);

}