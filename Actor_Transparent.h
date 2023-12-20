// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor_Transparent.generated.h"

UCLASS()
class REFUGEE_API AActor_Transparent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActor_Transparent();

	void SetTransParent(bool set);

private:
	UPROPERTY()
	TArray<class UMaterialInterface*> SMMaterialArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class UMaterialInterface* TransParentMaterial;

};
