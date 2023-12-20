// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor_FoodBox.generated.h"

UCLASS()
class REFUGEE_API AActor_FoodBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActor_FoodBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	bool CanCollect();
	void Collected();

private:
	UPROPERTY()
	bool bCollected = false;

	UPROPERTY()
	UParticleSystemComponent* FoodEffect;

};
