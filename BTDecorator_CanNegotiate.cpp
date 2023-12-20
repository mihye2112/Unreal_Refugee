// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CanNegotiate.h"
#include "AIController.h"
#include "Character_Enemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character_Player.h"
#include "Kismet/GameplayStatics.h"
#include "GameModeBase_InGame.h"

bool UBTDecorator_CanNegotiate::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	if (bResult == true)
	{
		APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
		if (IsValid(Pawn) == true)
		{
			ACharacter_Enemy* Character = Cast<ACharacter_Enemy>(Pawn);
			if (IsValid(Character) == true)
			{
				if (Character->IsNegotiating() == true)
				{
					return false;
				}

				AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld());
				if (IsValid(GameMode) == true)
				{
					AGameModeBase_InGame* InGameGameMode = Cast<AGameModeBase_InGame>(GameMode);
					if (IsValid(InGameGameMode) == true && InGameGameMode->CanNegotiate() == true)
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}