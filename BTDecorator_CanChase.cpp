// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CanChase.h"
#include "AIController.h"
#include "Character_Enemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameModeBase_InGame.h"

bool UBTDecorator_CanChase::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	if (bResult == true)
	{
		UObject* Obj = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target")));
		AActor* Actor = Cast<AActor>(Obj);
		if (IsValid(Actor) == true)
		{
			APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
			ACharacter_Enemy* Character = Cast<ACharacter_Enemy>(Pawn);
			if (IsValid(Character))
			{
				if (Character->IsNegotiating() == true)
				{
					return true;
				}

				float Distance = UKismetMathLibrary::Vector_Distance(Character->GetStartPos(), Actor->GetActorLocation());
				if (Distance <= (Character->GetPatrolRadius() * 2))
				{
					return true;
				}

				AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld());
				AGameModeBase_InGame* InGameGameMode = NULL;
				if (IsValid(GameMode) == true)
				{
					InGameGameMode = Cast<AGameModeBase_InGame>(GameMode);
					if (IsValid(InGameGameMode) == true)
					{
						InGameGameMode->RemoveChasingEnemy(Character);
					}
				}
			}
		}
	}	

	return false;
}