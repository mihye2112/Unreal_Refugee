// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "StaticMeshActor_Transparent.generated.h"

/**
 * 
 */
UCLASS()
class REFUGEE_API AStaticMeshActor_Transparent : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	void SetTransParent(bool set);

private:
	UPROPERTY()
	TArray<class UMaterialInterface*> SMMaterialArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class UMaterialInterface* TransParentMaterial;
};
