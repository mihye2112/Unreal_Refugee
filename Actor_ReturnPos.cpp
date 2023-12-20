// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_ReturnPos.h"
#include "Components/BoxComponent.h"
#include "Character_Player.h"
#include "Kismet/GameplayStatics.h"
#include "GameModeBase_InGame.h"

// Sets default values
AActor_ReturnPos::AActor_ReturnPos()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Trigger->SetCollisionProfileName(TEXT("Collectible"));
	Trigger->SetBoxExtent(FVector(125.f, 125.f, 15.f));
}

// Called when the game starts or when spawned
void AActor_ReturnPos::BeginPlay()
{
	Super::BeginPlay();

	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld());
	if (IsValid(GameMode) == true)
	{
		AGameModeBase_InGame* InGameGameMode = Cast<AGameModeBase_InGame>(GameMode);
		if (IsValid(InGameGameMode) == true)
		{
			InGameGameMode->SpawnReturnPosEffect(GetActorLocation());
		}
	}
}

void AActor_ReturnPos::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (IsValid(Trigger) == true)
	{
		Trigger->OnComponentBeginOverlap.AddDynamic(this, &AActor_ReturnPos::OnCharacterOverlap);
	}
}

void AActor_ReturnPos::OnCharacterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter_Player* Player = Cast<ACharacter_Player>(OtherActor);
	if (IsValid(Player) == true)
	{
		AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld());
		if (IsValid(GameMode) == true)
		{
			AGameModeBase_InGame* InGameGameMode = Cast<AGameModeBase_InGame>(GameMode);
			if (IsValid(InGameGameMode) == true)
			{
				InGameGameMode->GameClear();
			}
		}
	}
}
