// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CPPI_Villager.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UCPPI_Villager : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class CROPOUTSAMPLEPROJECT_API ICPPI_Villager
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ChangeJob(FName NewJob);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void PlayDeliverAnim(float& Delay);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void PlayWorkAnim(float Delay);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ProgressBuilding(float InvestedTime, float& TimeRemaining);

	//UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	//void Action(AActor Newparam);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ReturnToDefaultBT();
};
