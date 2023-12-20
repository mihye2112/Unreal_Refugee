// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Negotiate.h"
#include "AIController.h"
#include "Character_Enemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character_Player.h"
#include "Kismet/GameplayStatics.h"
#include "GameModeBase_InGame.h"

UBTTaskNode_Negotiate::UBTTaskNode_Negotiate()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTaskNode_Negotiate::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	FBTNegotiateTaskMemory* MyMemory = (FBTNegotiateTaskMemory*)NodeMemory;
	MyMemory->RemainingNegotiateTime = NegotiateTime;
	MyMemory->showCoinEffect = false;

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
					Character->StartNegotiate();
					Player->StartNegotiate(Character->GetActorLocation());

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

void UBTTaskNode_Negotiate::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	FBTNegotiateTaskMemory* MyMemory = (FBTNegotiateTaskMemory*)NodeMemory;
	MyMemory->RemainingNegotiateTime -= DeltaSeconds;

	if (MyMemory->RemainingNegotiateTime <= 0.0f)
	{
		APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
		if (IsValid(Pawn) == true)
		{
			ACharacter_Enemy* Character = Cast<ACharacter_Enemy>(Pawn);
			if (IsValid(Character) == true)
			{
				Character->EndNegotiate();
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

				AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld());
				if (IsValid(GameMode) == true)
				{
					AGameModeBase_InGame* InGameGameMode = Cast<AGameModeBase_InGame>(GameMode);
					if (IsValid(InGameGameMode) == true)
					{
						InGameGameMode->EndNegotiate();
					}
				}

				OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), nullptr);
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("PatrolPos")), Character->GetStartPos());
			}
		}
	}

	if (MyMemory->showCoinEffect == false && MyMemory->RemainingNegotiateTime <= 2.0f)
	{
		UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target")));
		if (IsValid(Target) == true)
		{
			ACharacter_Player* Player = Cast<ACharacter_Player>(Target);
			if (IsValid(Player) == true)
			{
				AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld());
				if (IsValid(GameMode) == true)
				{
					AGameModeBase_InGame* InGameGameMode = Cast<AGameModeBase_InGame>(GameMode);
					if (IsValid(InGameGameMode) == true)
					{
						FVector Location = Player->GetActorLocation();
						Location.Z += 120.f;
						InGameGameMode->NegotiateEffect(Location);
					}
				}
			}
		}

		MyMemory->showCoinEffect = true;
	}
}

uint16 UBTTaskNode_Negotiate::GetInstanceMemorySize() const
{
	return sizeof(FBTNegotiateTaskMemory);

}