// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Enum.h"
#include "CPPE_ResourceType.generated.h"

/**
 * 
 */
UCLASS()
class CROPOUTSAMPLEPROJECT_API UCPPE_ResourceType : public UBlackboardKeyType_Enum
{
	GENERATED_BODY()
	
};

UENUM(BlueprintType)
enum class EResourceType : uint8
{
	None,
	Food,
	Wood,
	Stone
};