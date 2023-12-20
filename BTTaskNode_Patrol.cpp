// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Patrol.h"
#include "AIController.h"
#include "Character_Enemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTaskNode_Patrol::UBTTaskNode_Patrol()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTaskNode_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (IsValid(Pawn) == true)
	{
		ACharacter_Enemy* Character = Cast<ACharacter_Enemy>(Pawn);
		if (IsValid(Character) == true)
		{
			FVector PatrolPos = OwnerComp.GetBlackboardComponent()->GetValueAsVector(FName(TEXT("PatrolPos")));
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(Character->Controller, PatrolPos);
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

void UBTTaskNode_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	ACharacter_Enemy* Character = Cast<ACharacter_Enemy>(Pawn);
	if (IsValid(Character) == true)
	{
		FVector PatrolPos = OwnerComp.GetBlackboardComponent()->GetValueAsVector(FName(TEXT("PatrolPos")));
		FVector Location = Character->GetActorLocation();
		Location.Z = 0.f;

		if (FVector::Dist(PatrolPos, Location) < 100.f)
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return;
		}
	}

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target")));
	if (IsValid(Target) == true)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

}