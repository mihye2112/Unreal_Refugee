// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_Base.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AnimInstanceBase.h"

// Sets default values
ACharacter_Base::ACharacter_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));

}

// Called when the game starts or when spawned
void ACharacter_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacter_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacter_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacter_Base::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	USkeletalMeshComponent* SkeletalMesh = GetMesh();
	if (IsValid(SkeletalMesh) == true)
	{
		UAnimInstance* Instance = SkeletalMesh->GetAnimInstance();
		if (IsValid(Instance) == true)
		{
			AnimInstance = Cast<UAnimInstance_Base>(Instance);
		}
	}
}

void ACharacter_Base::StartRun()
{	
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;

	if (IsValid(AnimInstance))
	{
		AnimInstance->StartRun();
	}
}

void ACharacter_Base::EndRun()
{	
	GetCharacterMovement()->MaxWalkSpeed = 200.f;


	if (IsValid(AnimInstance))
	{
		AnimInstance->EndRun();
	}
}

void ACharacter_Base::StartNegotiate()
{
	EndRun();
	bNegotiating = true;

}

void ACharacter_Base::EndNegotiate()
{
	bNegotiating = false;

}

