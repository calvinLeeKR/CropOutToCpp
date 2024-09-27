// Fill out your copyright notice in the Description page of Project Settings.


#include "CPPBP_Interactable.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACPPBP_Interactable::ACPPBP_Interactable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FVector Min01;
	FVector Max01;
	Mesh->GetLocalBounds(Min01, Max01);
	Max01 /= 100;
	FVector TempVector = FVector(
		fmax(100, fmax(round(Max01.X) * Step, round(Max01.Y) * Step)),
		fmax(100, fmax(round(Max01.X) * Step, round(Max01.Y) * Step)),
		fmax(100, round(Max01.Z) * Step)
	);
	Box->SetBoxExtent(TempVector + (BoundGap * 100), true);
	//Box->SetWorldRotation();
}

// Called when the game starts or when spawned
void ACPPBP_Interactable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPPBP_Interactable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPPBP_Interactable::TransformToTexture(FVector InVec, FVector2D& ReturnValue, FVector2D& ReturnValue2)
{
	FVector OriginOutput;
	FVector BoxExtentOutput;
	this->GetActorBounds(false, OriginOutput, BoxExtentOutput, false);
	float float01 = fminf(BoxExtentOutput.X, BoxExtentOutput.Y) / 10000.f
		* InVec.X * OutlineDraw;
	ReturnValue = FVector2D(
		((this->GetActorLocation() + 10000.f) / 20000.f * InVec.X) -
		(float01 / 2)
	);
	ReturnValue2 = FVector2D(float01, float01);
}

void ACPPBP_Interactable::PlacementMode()
{
	EnableGroundBlend = false;
	Mesh->SetStaticMesh(MeshList[0]);
	this->Tags.Empty();
	this->Tags.Add(FName("PlacementMode"));
}

