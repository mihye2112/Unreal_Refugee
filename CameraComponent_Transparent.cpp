// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraComponent_Transparent.h"
#include "StaticMeshActor_Transparent.h"
#include "GameFramework/PlayerController.h"
#include "Actor_Transparent.h"

UCameraComponent_Transparent::UCameraComponent_Transparent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCameraComponent_Transparent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TArray<FHitResult> HitResultArray;
	UGameInstance* Instance = GetWorld()->GetGameInstance();
	APlayerController* Controller = Instance->GetFirstLocalPlayerController();
	FVector Start = GetComponentLocation();
	FVector End = Controller->GetPawn()->GetActorLocation();
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery9);
	FCollisionObjectQueryParams params(ObjectTypes);
	bool result = GetWorld()->LineTraceMultiByObjectType(HitResultArray, Start, End, params);
	TArray<class AStaticMeshActor_Transparent*> TempArray;
	TArray<class AActor_Transparent*> TempActorArray;

	if (result == true)
	{
		for (FHitResult& hitResult : HitResultArray)
		{
			AActor* Actor = hitResult.GetActor();
			if (IsValid(Actor) == true)
			{
				AStaticMeshActor_Transparent* Transparent = Cast<AStaticMeshActor_Transparent>(Actor);
				if (IsValid(Transparent) == true)
				{
					TempArray.Add(Transparent);
					continue;
				}

				AActor_Transparent* TransparentActor = Cast<AActor_Transparent>(Actor);
				if (IsValid(TransparentActor) == true)
				{
					TempActorArray.Add(TransparentActor);
				}
			}
		}
	}

	for (int index = SMAArray.Num() - 1; index >= 0; index--)
	{
		if (TempArray.Contains(SMAArray[index]) == false)
		{
			SMAArray[index]->SetTransParent(false);
			SMAArray.RemoveAt(index);
		}
	}

	for (int index = TempArray.Num() - 1; index >= 0; index--)
	{
		if (SMAArray.Contains(TempArray[index]) == false)
		{
			SMAArray.Add(TempArray[index]);
			TempArray[index]->SetTransParent(true);
		}
	}

	for (int index = ActorArray.Num() - 1; index >= 0; index--)
	{
		if (TempActorArray.Contains(ActorArray[index]) == false)
		{
			ActorArray[index]->SetTransParent(false);
			ActorArray.RemoveAt(index);
		}
	}

	for (int index = TempActorArray.Num() - 1; index >= 0; index--)
	{
		if (ActorArray.Contains(TempActorArray[index]) == false)
		{
			ActorArray.Add(TempActorArray[index]);
			TempActorArray[index]->SetTransParent(true);
		}
	}
}