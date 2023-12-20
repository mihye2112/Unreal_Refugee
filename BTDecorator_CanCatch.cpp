// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CanCatch.h"
#include "AIController.h"
#include "Character_Enemy.h"
#include "Character_Player.h"
#include "Kismet/GameplayStatics.h"
#include "GameModeBase_InGame.h"

bool UBTDecorator_CanCatch::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
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
				AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld());
				AGameModeBase_InGame* InGameGameMode = NULL;
				if (IsValid(GameMode) == true)
				{
					InGameGameMode = Cast<AGameModeBase_InGame>(GameMode);
				}

				if (Character->IsNegotiating() == true)
				{
					if (IsValid(InGameGameMode) == true)
					{
						InGameGameMode->RemoveChasingEnemy(Character);
					}

					return true;
				}

				FHitResult HitResult;
				FVector Start = Character->GetActorLocation() - Character->GetActorForwardVector() * 17.f;
				FVector End = Character->GetActorLocation() + Character->GetActorForwardVector() * 17.f;
				FCollisionQueryParams Params(NAME_None, false, Character);

				bool bCollisionResult = GetWorld()->SweepSingleByChannel(OUT HitResult, Start, End, FQuat::Identity,
					ECollisionChannel::ECC_EngineTraceChannel2, FCollisionShape::MakeCapsule(34.f, 88.f),
					Params);

				if (bCollisionResult == true && HitResult.Actor.IsValid() == true)
				{
					ACharacter_Player* Player = Cast<ACharacter_Player>(HitResult.Actor);
					if (IsValid(Player) == true)
					{
						if (IsValid(InGameGameMode) == true)
						{
							InGameGameMode->RemoveChasingEnemy(Character);
						}

						return true;
					}
				}
			}
		}
	}

	return false;
}