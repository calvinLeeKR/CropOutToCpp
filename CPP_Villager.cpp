// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CPP_Villager.h"
#include "Components/CapsuleComponent.h"
#include "Components/DecalComponent.h"


// Sets default values
ACPP_Villager::ACPP_Villager()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//subobject creatings
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	Tool = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TOOL"));
	Hat = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HAT"));
	Hair = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HAIR"));
	Decal = CreateDefaultSubobject<UDecalComponent>(TEXT("DECAL"));
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVEMENT"));

	//attachment settings
	RootComponent = Capsule;
	Mesh->SetupAttachment(Capsule);
	Tool->SetupAttachment(Mesh);
	Hat->SetupAttachment(Mesh);
	Hair->SetupAttachment(Mesh);
	Decal->SetupAttachment(Capsule);

	//component settings
	Capsule->SetCapsuleHalfHeight(92.038315f);
	Capsule->SetCapsuleRadius(30.0f);
	Mesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -92.561032), FRotator(0.0f, -90.0f, 0.0f));
	Decal->SetRelativeLocationAndRotation(FVector(0.000001, -0.000000, -94.502671), FRotator(-90.000000, 360.000000, 0.000000));
	Decal->SetRelativeScale3D(FVector(0.437500, 0.343750, 0.343750));

	//animation settings
	Mesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimSequence> MESH_ANIM
	(TEXT("/Script/Engine.AnimBlueprint'/Game/Characters/Animations/ABP_Villager.ABP_Villager'"));
	if (MESH_ANIM.Succeeded()) {
		UAnimationAsset* meshAnimInstance = Cast<UAnimationAsset>(MESH_ANIM.Class);
		Mesh->SetAnimation(meshAnimInstance);
	}
	Hat->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> HAT_ANIM
	(TEXT("/Script/Engine.AnimBlueprint'/Game/Characters/Meshes/Hats/ABP_Hat.ABP_Hat'"));
	if (HAT_ANIM.Succeeded())
		Hat->SetAnimInstanceClass(HAT_ANIM.Class);

	//materials settings
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SKM_VILLAGER
	(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Meshes/SKM_Villager.SKM_Villager'"));
	if (SKM_VILLAGER.Succeeded())
		Mesh->SetSkeletalMesh(SKM_VILLAGER.Object);
	static ConstructorHelpers::FObjectFinder<UMaterial> DECAL_MAT
	(TEXT("/Script/Engine.Material'/Game/Characters/Materials/MD_Shadow.MD_Shadow'"));
	if (DECAL_MAT.Succeeded()) {
		UMaterial* selectedDecalMat = DECAL_MAT.Object;
		Decal->SetMaterial(0, selectedDecalMat);
	}
}

// Called when the game starts or when spawned
void ACPP_Villager::BeginPlay()
{
	Super::BeginPlay();
	FHitResult HitResult;
	AddActorWorldOffset(FVector(0.0f, 0.0f, 0.0f), false, &HitResult, ETeleportType::None);

	Mesh->SetCustomDepthStencilValue(FMath::FRandRange(0.0f, 1.0f));
}

// Called every frame
void ACPP_Villager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPP_Villager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACPP_Villager::Eat() {
	UGameplayStatics::GetGameMode(this);
}

/*void ACPP_Villager::ResetJobState()
{
}

void ACPP_Villager::StopJob()
{
}

void ACPP_Villager::HairPick()
{
}*/

