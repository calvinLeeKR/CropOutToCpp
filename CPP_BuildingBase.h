// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_Interactable.h"
#include "CPP_BuildingBase.generated.h"

/**
 * 
 */
UCLASS()
class CROPOUTSAMPLEPROJECT_API ACPP_BuildingBase : public ACPP_Interactable
{
	GENERATED_BODY()

public:
	ACPP_BuildingBase();
	float ProgressConstruct(float InvestedTime);
	float Interact();
	void SpawnInBuildMode(float Progression);
	void ConstructionComplete();
public:
	//variables
	float BuildDifficulty = 1.0f;
	int CurrentStage;
};
