// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CPPI_GI.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCPPI_GI : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CROPOUTSAMPLEPROJECT_API ICPPI_GI
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RetrieveSaveData")
	void CheckSaveBool(bool& SaveExist);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RetrieveSaveData")
	void GetSeed(FRandomStream& Seed);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RetrieveSaveData")
	void GetAllInteractables();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RetrieveSaveData")
	void GetSave();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SetSaveData")
	void LoadLevel();

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ClearSave(bool& ClearSeed);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateAllVillagers();
};
