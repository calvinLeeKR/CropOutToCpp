// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Interactable.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h" //DelayUntilNextTick
#include "Kismet/KismetRenderingLibrary.h" //DrawCanvas, et
#include "Engine/Canvas.h" //Canvas

// Sets default values
ACPP_Interactable::ACPP_Interactable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// PrimaryActorTick.bCanEverTick = true;
	FVector Min01;
	FVector Max01;
	if (Mesh) {
		Mesh->GetLocalBounds(Min01, Max01);
		Max01 = Max01 / 100;
		FVector TempVector = FVector(
			fmax(100, fmax(round(Max01.X) * Step, round(Max01.Y) * Step)),
			fmax(100, fmax(round(Max01.X) * Step, round(Max01.Y) * Step)),
			fmax(100, round(Max01.Z) * Step)
		);
		Box->SetBoxExtent(TempVector + (BoundGap * 100), true);
		FRotator WorldRot = UKismetMathLibrary::MakeRotFromX(FVector::XAxisVector);
		Box->SetWorldRotation(WorldRot);
	}
}

// Called when the game starts or when spawned
void ACPP_Interactable::BeginPlay()
{
	Super::BeginPlay();

	//objects settings
	//none, interface class

	

	FLatentActionInfo flai;
	flai.CallbackTarget = this;
	flai.ExecutionFunction = FName("DelayUntilNextTick"); //go to this->DelayUntilNexTick()
	flai.Linkage = 1;
	flai.UUID = 0; //FLatentActionInfo struct, similar as delegate

	UKismetSystemLibrary::DelayUntilNextTick(GetWorld(), flai);
	//construction script part
}

// Called every frame
void ACPP_Interactable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_Interactable::TransformToTexture(FVector2D InVec, FVector2D& ReturnValue, FVector2D& ReturnValue2)
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

void ACPP_Interactable::DelayUntilNextTick()
{
	UCanvas* canvas;
	FVector2D size;
	FDrawToRenderTargetContext context; //prepare address return
	
	FVector2D return1;
	FVector2D return2;

	TSet<AActor*> Overlapped_actors;
	TSubclassOf<ACPP_Interactable> Interactablie_Filter;

	//prepare variables
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Mat_Ifc
		(TEXT("/Script/Engine.Material'/Game/Environment/Materials/M_ShapeDraw.M_ShapeDraw'"));
	if (Mat_Ifc.Succeeded()) {
		umi = Mat_Ifc.Object;
	}
	//prepare objects

	if (EnableGroundBlend) {
		UKismetRenderingLibrary::BeginDrawCanvasToRenderTarget(GetWorld(), RT_DRAW, canvas, size, context);
		TransformToTexture(size, return1, return2);
		canvas->K2_DrawMaterial(umi, return1, return2,
			{ 0.0f, 0.0f }, { 1.0f, 1.0f });
		UKismetRenderingLibrary::EndDrawCanvasToRenderTarget(GetWorld(), context);
	}

	this->GetOverlappingActors(Overlapped_actors, Interactablie_Filter);
	for (auto ia : Overlapped_actors) {
		if (!ia->ActorHasTag(FName("PlacementMode")) && UKismetMathLibrary::EqualEqual_VectorVector(ia->GetActorLocation(), this->GetActorLocation(), 5.0f)) {
			ia->K2_DestroyActor();
		}
	}
}

void ACPP_Interactable::PlacementMode()
{
	EnableGroundBlend = false;
	Mesh->SetStaticMesh(MeshList[0]);
	this->Tags.Empty();
	this->Tags.Add(FName("PlacementMode"));
}

void ACPP_Interactable::PlayWobble(FVector NewParam)
{
	FVector toNormalVec = NewParam - this->GetActorLocation();
	UKismetMathLibrary::Vector_Normalize(toNormalVec, 0.0001f);
	Mesh->SetVectorParameterValueOnMaterials(FName("Wobble Vector"), toNormalVec);

}


