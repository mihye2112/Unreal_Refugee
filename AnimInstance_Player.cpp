// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance_Player.h"
#include "Character_Player.h"

void UAnimInstance_Player::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* Pawn = TryGetPawnOwner();
	if (IsValid(Pawn) == true)
	{
		ACharacter_Player* PlayerCharacter = Cast<ACharacter_Player>(Pawn);
		if (IsValid(PlayerCharacter) == true)
		{
			FwdBwdValue = PlayerCharacter->GetFwdBwdValue();
		}
	}
}