// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CPPI_Resource.h"
#include "CPPI_Villager.h"
#include "CPP_Villager.generated.h"

UCLASS()
class CROPOUTSAMPLEPROJECT_API ACPP_Villager : public APawn, public ICPPI_Villager, public ICPPI_Resource
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACPP_Villager();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Tool;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Hat;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Hair;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UDecalComponent* Decal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UFloatingPawnMovement* Movement;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// user defined functions
	const void Eat();
	const void ResetJobState();
	const void StopJob();
	FSoftObjectPath HairPick();
public:
	//event calling functions
	void ReturnToIdle();

	virtual void ReturnToDefaultBT_Implementation() override;

	void PlayVillagerAnim(UAnimMontage* Montage, float length);

	virtual void Action_Implementation(AActor* ParamActor) override;

	virtual void ChangeJob_Implementation(FName NewJob) override;
		FSoftObjectPath sop_BehaviorTree;
		void OnLoadComplete_BehaviorTree();
		FSoftObjectPath sop_WorkAnim;
		void OnLoadComplete_AnimMontage();
		FSoftObjectPath sop_Hat;
		void OnLoadComplete_HatSkeletal();
		FSoftObjectPath sop_Tool;
		void OnLoadComplete_ToolSkeletal();
	virtual void PlayWorkAnim_Implementation(float Delay) override;

public:
	//subobjects
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JobProfile", meta = (AllowPrivateAccess = "true"))
	AActor* Target_Ref;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JobProfile", meta = (AllowPrivateAccess = "true"))
	FName New_Job;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JobProfile", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* Work_Anim;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JobProfile", meta = (AllowPrivateAccess = "true"))
	UStaticMesh* Target_Tool;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JobProfile")
	UBehaviorTree* ActiveBehavior;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource", meta = (AllowPrivateAccess = "true"))
	int Quantity;
};