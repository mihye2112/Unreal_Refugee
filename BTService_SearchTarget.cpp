// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SearchTarget.h"
#include "AIController.h"
#include "Character_Player.h"
#include "Character_Enemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_SearchTarget::UBTService_SearchTarget()
{
	bTickIntervals = 1.0f;
}

void UBTService_SearchTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (IsValid(Pawn) == true)
	{
		ACharacter_Enemy* Character = Cast<ACharacter_Enemy>(Pawn);
		if (IsValid(Character) == true && Character->IsNegotiated() == true)
		{
			return;
		}

		TArray<FOverlapResult> OverlapResultArray;
		FVector Pos = Pawn->GetActorLocation();
		FCollisionQueryParams Params(NAME_None, false, Pawn);
		bool bResult = GetWorld()->OverlapMultiByChannel(OverlapResultArray, Pos, FQuat::Identity,
			ECollisionChannel::ECC_EngineTraceChannel2, FCollisionShape::MakeSphere(Character->GetPatrolRadius()), Params);

		//DrawDebugSphere(GetWorld(), Pos, Character->GetPatrolRadius(), 16, FColor::Red, false, 0.5f);

		if (bResult == true)
		{
			for (FOverlapResult& result : OverlapResultArray)
			{
				AActor* Actor = result.GetActor();
				if (IsValid(Actor) == true)
				{
					ACharacter_Player* Player = Cast<ACharacter_Player>(Actor);
					if (IsValid(Player) == true)
					{
						FName Name = FName(TEXT("Target"));
						OwnerComp.GetBlackboardComponent()->SetValueAsObject(Name, Player);
					}
				}
			}
		}
	}

}
