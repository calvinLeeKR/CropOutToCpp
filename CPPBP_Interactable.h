// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetRenderingLibrary.h" //UTextureRenderTarget2D
#include "Components/TimelineComponent.h" //UTimelineComponent
#include "Components/BoxComponent.h" //box collision
#include "CPPBP_Interactable.generated.h"

UCLASS()
class CROPOUTSAMPLEPROJECT_API ACPPBP_Interactable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPPBP_Interactable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	//variables
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UTimelineComponent* Timeline_0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* Box;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* Scene;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GroundBlend", meta = (AllowPrivateAccess = "true"))
	UTextureRenderTarget2D* RT_DRAW;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GroundBlend", meta = (AllowPrivateAccess = "true"))
	float OutlineDraw;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GroundBlend", meta = (AllowPrivateAccess = "true"))
	bool EnableGroundBlend;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Progression", meta = (AllowPrivateAccess = "true"))
	bool RequireBuild;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Progression", meta = (AllowPrivateAccess = "true"))
	float ProgressionState;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Progression", meta = (AllowPrivateAccess = "true"))
	TArray<UStaticMesh*> MeshList;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpawnInfo", meta = (AllowPrivateAccess = "true"))
	float BoundGap;

	//local 
	float Step = 100.f;
public:
	//blueprint macro
	void TransformToTexture(FVector InVec, FVector2D& ReturnValue, FVector2D& ReturnValue2);
public:
	//functions
	void PlacementMode();
	float Interact() { return 0.f; };
};
