// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CPPE_ResourceType.h"
#include "CPPI_Resource.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UCPPI_Resource : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CROPOUTSAMPLEPROJECT_API ICPPI_Resource
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ResourceManagement")
		void RemoveResource(EResourceType& TargetResource, int32& Value);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ResourceManagement")
		void AddResource(EResourceType Resource, int32 Value);

	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ResourceManagement")
	//	void GetCurrentResource(TMap<int32, EResourceType> Resources);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ResourceManagement")
		void RemoveTargetResource(EResourceType NewParam, int32 NewParam1);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ResourceManagement")
		void CheckResource(EResourceType NewParam1, bool& NewParam, int32& NewParam3);

};
