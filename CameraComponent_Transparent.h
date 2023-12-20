// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "CameraComponent_Transparent.generated.h"

/**
 * 
 */
UCLASS()
class REFUGEE_API UCameraComponent_Transparent : public UCameraComponent
{
	GENERATED_BODY()

	UCameraComponent_Transparent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	UPROPERTY()
	TArray<class AStaticMeshActor_Transparent*> SMAArray;
	UPROPERTY()
	TArray<class AActor_Transparent*> ActorArray;
};
