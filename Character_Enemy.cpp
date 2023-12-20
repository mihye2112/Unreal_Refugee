// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_Enemy.h"
#include "AIController_Enemy.h"
#include "DrawDebugHelpers.h"

ACharacter_Enemy::ACharacter_Enemy()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AAIController_Enemy::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ACharacter_Enemy::BeginPlay()
{
	Super::BeginPlay();
	
	StartPos = GetActorLocation();

	//DrawDebugSphere(GetWorld(), StartPos, PatrolRadius, 16, FColor::Green, true);
}

FVector ACharacter_Enemy::GetStartPos()
{
	return StartPos;

}

float ACharacter_Enemy::GetPatrolRadius()
{
	return PatrolRadius;

}

bool ACharacter_Enemy::IsNegotiating()
{
	return bNegotiating;

}

bool ACharacter_Enemy::IsNegotiated()
{
	return bIsNegotiated;

}

void ACharacter_Enemy::EndNegotiate()
{
	Super::EndNegotiate();
	bIsNegotiated = true;
}

