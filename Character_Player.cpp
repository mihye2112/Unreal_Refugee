// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_Player.h"

#include "GameFramework/SpringArmComponent.h"
#include "CameraComponent_Transparent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameModeBase_InGame.h"
#include "Kismet/KismetMathLibrary.h"
#include "AnimInstanceBase.h"
#include "Actor_FoodBox.h"

ACharacter_Player::ACharacter_Player()
{
	PrimaryActorTick.bCanEverTick = true;

	UWorld* World = GetWorld();
	if (IsValid(World) == true)
	{
		AGameModeBase* GameMode = UGameplayStatics::GetGameMode(World);
		if (IsValid(GameMode) == true)
		{
			InGameGameMode = Cast<AGameModeBase_InGame>(GameMode);
		}
	}
}

void ACharacter_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsRunning() == true)
	{
		float StaminaValue = Stamina - StaminaAdjustValue * DeltaTime;
		SetStamina(StaminaValue);

		if (Stamina <= 0.f)
		{
			SetStamina(0.f);
			EndRun();
		}
	}
	else
	{
		if (Stamina < AGameModeBase_InGame::MaxStamina)
		{
			float StaminaValue = Stamina + StaminaAdjustValue * DeltaTime;
			SetStamina(StaminaValue);

			if (Stamina >= AGameModeBase_InGame::MaxStamina)
			{
				SetStamina(AGameModeBase_InGame::MaxStamina);
			}
		}

		if (bRunActionCalled == true && FwdBwdValue > 0.f && Stamina > 0.f)
		{
			Super::StartRun();
		}
	}

	if (bNegotiating == true)
	{
		FRotator InterpRotation = UKismetMathLibrary::RInterpTo(GetController()->GetControlRotation(), NegotiationStartRot, DeltaTime, 5.f);
		GetController()->SetControlRotation(FRotator(InterpRotation.Pitch, InterpRotation.Yaw, GetController()->GetControlRotation().Roll));
	}

	if (bCollecting == true && bFoodBoxOverlapped == true)
	{
		if (IsValid(InGameGameMode) == true)
		{
			InGameGameMode->Collecting(CollectingTime);
		}

		if (CollectingTime >= AGameModeBase_InGame::CollectTime)
		{
			Collected();
		}

		CollectingTime += DeltaTime;
	}
}

void ACharacter_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("FwdBwd"), this, &ACharacter_Player::FwdBwd);
	PlayerInputComponent->BindAxis(TEXT("Yaw"), this, &ACharacter_Player::Yaw);

	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Pressed, this, &ACharacter_Player::StartRun);
	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Released, this, &ACharacter_Player::EndRun);

	PlayerInputComponent->BindAction(TEXT("Collect"), EInputEvent::IE_Pressed, this, &ACharacter_Player::StartCollect);
	PlayerInputComponent->BindAction(TEXT("Collect"), EInputEvent::IE_Released, this, &ACharacter_Player::EndCollect);
}

void ACharacter_Player::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACharacter_Player::OnBeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ACharacter_Player::OnEndOverlap);
}

void ACharacter_Player::BeginPlay()
{
	Super::BeginPlay();

	SetStamina(AGameModeBase_InGame::MaxStamina);
}

void ACharacter_Player::StartRun()
{
	if (IsRunning() == true)
	{
		return;
	}

	Super::StartRun();
	  
	bRunActionCalled = true;
}

void ACharacter_Player::EndRun()
{
	Super::EndRun();

	bRunActionCalled = false;
}

void ACharacter_Player::StartNegotiate(FVector TargetLocation)
{
	Super::StartNegotiate();

	IgnoreInput(true);

	NegotiationStartRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);

	if (IsValid(InGameGameMode) == true)
	{
		InGameGameMode->UseCoin();
	}
}

void ACharacter_Player::EndNegotiate()
{
	Super::EndNegotiate();

	IgnoreInput(false);
}

float ACharacter_Player::GetFwdBwdValue()
{
	return FwdBwdValue;
}

void ACharacter_Player::BeCaught()
{
	if (IsValid(InGameGameMode) == true)
	{
		InGameGameMode->GameOver();
	}
}

void ACharacter_Player::FwdBwd(float Value)
{
	FwdBwdValue = Value;
	AddMovementInput(GetActorForwardVector(), FwdBwdValue);

	if (IsRunning() == true && FwdBwdValue <= 0.f)
	{
		Super::EndRun();
	}
}

void ACharacter_Player::Yaw(float Value)
{
	AddControllerYawInput(Value);
}

void ACharacter_Player::StartCollect()
{
	bCollecting = true;
	CollectingTime = 0.f;

	IgnoreInput(true);
}

void ACharacter_Player::EndCollect()
{
	bCollecting = false;
	CollectingTime = 0.f;

	IgnoreInput(false);

	if (IsValid(InGameGameMode) == true)
	{
		InGameGameMode->EndCollect();
	}
}

void ACharacter_Player::Collected()
{
	EndCollect();

	bFoodBoxOverlapped = false;

	OnCollected.Broadcast();
	OnCollected.Clear();

	if (IsValid(InGameGameMode) == true)
	{
		InGameGameMode->Collect();
	}
}

void ACharacter_Player::IgnoreInput(bool bIgnore)
{
	if (IsValid(Controller) == true)
	{
		if (bIgnore == true)
		{
			Controller->SetIgnoreMoveInput(true);
			Controller->SetIgnoreLookInput(true);
		}
		else
		{
			Controller->ResetIgnoreMoveInput();
			Controller->ResetIgnoreLookInput();
		}
	}
}

bool ACharacter_Player::IsRunning()
{
	if (IsValid(AnimInstance) == true && AnimInstance->IsRunning() == true)
	{
		return true;
	}

	return false;
}

void ACharacter_Player::SetStamina(float Value)
{
	Stamina = Value;

	if (IsValid(InGameGameMode) == true)
	{
		InGameGameMode->UpdateStamina(Stamina);
	}
}

void ACharacter_Player::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AActor_FoodBox* FoodBox = Cast<AActor_FoodBox>(OtherActor);
	if (IsValid(FoodBox) && FoodBox->CanCollect() == true)
	{
		bFoodBoxOverlapped = true;
		OnCollected.AddUObject(FoodBox, &AActor_FoodBox::Collected);
	}
}

void ACharacter_Player::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AActor_FoodBox* FoodBox = Cast<AActor_FoodBox>(OtherActor);
	if (IsValid(FoodBox))
	{
		bFoodBoxOverlapped = false;		
		OnCollected.Clear();
	}
}