// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Chase.h"
#include "AIController.h"
#include "Character_Enemy.h"
#include "Character_Player.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameModeBase_InGame.h"

EBTNodeResult::Type UBTTaskNode_Chase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (IsValid(Pawn) == true)
	{
		ACharacter_Enemy* Character = Cast<ACharacter_Enemy>(Pawn);
		if (IsValid(Character) == true)
		{
			UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target")));
			if (IsValid(Target) == true)
			{
				ACharacter_Player* Player = Cast<ACharacter_Player>(Target);
				if (IsValid(Player) == true)
				{
					UAIBlueprintHelperLibrary::SimpleMoveToActor(Character->Controller, Player);
					Character->StartRun();

					AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld());
					if (IsValid(GameMode) == true)
					{
						AGameModeBase_InGame* InGameGameMode = Cast<AGameModeBase_InGame>(GameMode);
						if (IsValid(InGameGameMode) == true)
						{
							InGameGameMode->AddChasingEnemy(Character);
						}
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
	}

	return Result;
}