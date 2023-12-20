// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticMeshActor_Transparent.h"
#include "Components/StaticMeshComponent.h"

void AStaticMeshActor_Transparent::SetTransParent(bool set)
{
	TArray<UStaticMeshComponent*> Components;
	GetComponents<UStaticMeshComponent>(Components);
	if (set == true)
	{		
		for (int32 i = 0; i < Components.Num(); i++)
		{
			UStaticMeshComponent* SMC = Components[i];
			TArray<class UMaterialInterface*> Array = SMC->GetMaterials();
			for (int index = 0; index < Array.Num(); index++)
			{
				SMMaterialArray.Add(Array[index]);
			}

			for (int materialIndex = 0; materialIndex < SMMaterialArray.Num(); materialIndex++)
			{
				SMC->SetMaterial(materialIndex, TransParentMaterial);
			}
		}
	}
	else
	{
		int arrayIndex = 0;
		for (int32 i = 0; i < Components.Num(); i++)
		{
			UStaticMeshComponent* SMC = Components[i];
			TArray<class UMaterialInterface*> Array = SMC->GetMaterials();
			for (int materialIndex = 0; materialIndex < Array.Num(); materialIndex++)
			{
				SMC->SetMaterial(materialIndex, SMMaterialArray[arrayIndex]);
				arrayIndex++;
			}
		}
	}
}