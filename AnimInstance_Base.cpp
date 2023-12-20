// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance_Base.h"

void UAnimInstance_Base::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* Pawn = TryGetPawnOwner();
	if (IsValid(Pawn) == true)
	{
		Speed = Pawn->GetVelocity().Size();
	}
}

void UAnimInstance_Base::StartRun()
{
	bIsRunning = true;
}

void UAnimInstance_Base::EndRun()
{
	bIsRunning = false;
}

bool UAnimInstance_Base::IsRunning()
{
	return bIsRunning;
}