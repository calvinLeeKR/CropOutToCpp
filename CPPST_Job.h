// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Datatable.h"
#include "Engine/UserDefinedStruct.h"
#include "CPPST_Job.generated.h"

/**
 * 
 */
class UBehaviorTree;

UCLASS()
class CROPOUTSAMPLEPROJECT_API UCPPST_Job : public UUserDefinedStruct
{
	GENERATED_BODY()
};

USTRUCT(BlueprintType, Atomic)
struct FST_Jobs : public FTableRowBase {
	GENERATED_USTRUCT_BODY()
public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	UBehaviorTree* BehaviourTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* WorkAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* Hat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* Tools;
};
