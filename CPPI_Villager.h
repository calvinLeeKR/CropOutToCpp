// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CPPST_Job.h"
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
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ChangeJob(FName NewJob);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PlayDeliverAnim(float& Delay);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PlayWorkAnim(float Delay);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ProgressBuilding(float InvestedTime, float& TimeRemaining);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Action(AActor* ParamActor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ReturnToDefaultBT();
};
