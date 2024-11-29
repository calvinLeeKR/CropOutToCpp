// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_BuildingBase.h"
#include "Kismet/KismetMathLibrary.h"

ACPP_BuildingBase::ACPP_BuildingBase()
{
}

float ACPP_BuildingBase::ProgressConstruct(float InvestedTime)
{
	ProgressionState += InvestedTime / BuildDifficulty;
	if (ProgressionState >= MeshList.Num()) { //build complete
		this->ConstructionComplete();
		Mesh->SetStaticMesh(MeshList.Last());
		GetGameInstance();
		//updateallinteractables
	}
	else {
		if (UKismetMathLibrary::FFloor(ProgressionState) > CurrentStage) {
			CurrentStage = UKismetMathLibrary::FFloor(ProgressionState);
			if (MeshList[CurrentStage]) {
				Mesh->SetStaticMesh(MeshList[CurrentStage]);
				GetGameInstance();
				//updateallinteractables
			}
		}
	}
	return 0.0f;
}


float ACPP_BuildingBase::Interact()
{
	Super::Interact();

	return 0.0f;
}

void ACPP_BuildingBase::SpawnInBuildMode(float Progression)
{
	ProgressionState = Progression;
	Tags.Add(FName("Build"));
	if (MeshList[UKismetMathLibrary::FTrunc(ProgressionState * MeshList.Num())]) {
		Mesh->SetStaticMesh(MeshList[UKismetMathLibrary::FTrunc(ProgressionState * MeshList.Num())]);
	}
}

void ACPP_BuildingBase::ConstructionComplete()
{
	Tags.Remove(FName("Build"));
	GetGameInstance();
	//updateallinteractables
}
