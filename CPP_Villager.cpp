// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CPP_Villager.h"
#include "Components/CapsuleComponent.h"
#include "Components/DecalComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/AssetManager.h"
#include "Engine/ObjectLibrary.h"
#include "cstring"

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

UFUNCTION(BlueprintImplementableEvent, Category = "MyVillagerFunction")
const void ACPP_Villager::Eat() {
	UGameplayStatics::GetGameMode(this);
}


// Called when the game starts or when spawned
void ACPP_Villager::BeginPlay()
{
	Super::BeginPlay();
	FHitResult HitResult;
	AddActorWorldOffset(FVector(0.0f, 0.0f, 0.0f), false, &HitResult, ETeleportType::None);

	Mesh->SetCustomPrimitiveDataFloat(0, FMath::FRandRange(0.0f, 1.0f));
	Mesh->SetCustomPrimitiveDataFloat(1, FMath::FRandRange(0.0f, 1.0f));
	AddActorWorldOffset(FVector(0.0f, 0.0f, Capsule->GetScaledCapsuleHalfHeight()), false, &HitResult, ETeleportType::None);
	//set ai controller
	AIControllerClass = AAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	//set timer
	FTimerHandle TimerHandle_EatDelay;
	FTimerDelegate TimerDelegate;
	//TimerDelegate.BindUFunction(this, FName("Eat"));
	GetWorldTimerManager().SetTimer(TimerHandle_EatDelay, 24.0f, false);
	//softobject path creating via function
	UObjectLibrary* lib = UObjectLibrary::CreateLibrary(USkeletalMesh::StaticClass(), false, GIsEditor);
	lib->AddToRoot();
	FSoftObjectPath PickedHair = ACPP_Villager::HairPick();
	lib->LoadAssetDataFromPath(PickedHair.GetAssetPathString());
	lib->LoadAssetsFromAssetData();
	//async load
	auto& StreamManager = UAssetManager::Get().GetStreamableManager();
	StreamManager.RequestAsyncLoad(PickedHair);
	if (StreamManager.IsAsyncLoadComplete(PickedHair)) {
		Hair->SetSkeletalMeshAsset(Cast<USkeletalMesh>(PickedHair.ResolveObject()));
	} //get loaded mesh if success, and set asset
	Hair->SetCustomPrimitiveDataFloat(0, FMath::FRandRange(0.0f, 1.0f));

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

UFUNCTION(BlueprintImplementableEvent, Category = "MyVillagerFunction")
const void ACPP_Villager::ResetJobState()
{
	Hat->SetSkeletalMeshAsset(NULL);
	Tool->SetVisibility(false, false);
	Tool->SetStaticMesh(NULL);
	Target_Tool = NULL;
}

UFUNCTION(BlueprintImplementableEvent, Category = "MyVillagerFunction")
const void ACPP_Villager::StopJob()
{
	Tool->SetVisibility(false, false);
	Mesh->GetAnimInstance()->Montage_StopGroupByName(0.0f, FName("DefaultGroup"));

	if (this->GetController()) {
		this->GetController()->StopMovement();
	}

	Quantity = 0;
}

UFUNCTION(BlueprintImplementableEvent, Category = "MyVillagerFunction")
FSoftObjectPath ACPP_Villager::HairPick()
{
	TCHAR toReturnMeshAddress[80] = {};

	switch (FMath::RandRange(0, 5)) {
	case 0:
		_tcscpy(toReturnMeshAddress, L"/Script/Engine.SkeletalMesh'/Game/Characters/Meshes/Hair/SKM_Hair01.SKM_Hair01'"); break;
		
	case 1:
		_tcscpy(toReturnMeshAddress, L"/Script/Engine.SkeletalMesh'/Game/Characters/Meshes/Hair/SKM_Hair02.SKM_Hair02'"); break;
		
	case 2:
		_tcscpy(toReturnMeshAddress, L"/Script/Engine.SkeletalMesh'/Game/Characters/Meshes/Hair/SKM_Hair03.SKM_Hair03'"); break;
		
	case 3:
		_tcscpy(toReturnMeshAddress, L"/Script/Engine.SkeletalMesh'/Game/Characters/Meshes/Hair/SKM_Hair04.SKM_Hair04'"); break;
		
	case 4:
		_tcscpy(toReturnMeshAddress, L"/Script/Engine.SkeletalMesh'/Game/Characters/Meshes/Hair/SKM_Hair05.SKM_Hair05'"); break;
		
	case 5:
		_tcscpy(toReturnMeshAddress, L"/Script/Engine.SkeletalMesh'/Game/Characters/Meshes/Hair/SKM_Hair06.SKM_Hair06'"); break;
	}
	/*static ConstructorHelpers::FObjectFinder<USkeletalMesh> RETURN_MESH
	(toReturnMeshAddress);
	if (RETURN_MESH.Succeeded()) { return Cast<USkeletalMesh>(RETURN_MESH.Object); }
	return nullptr;*/
	FSoftObjectPath ReturnSkeletalPath(toReturnMeshAddress);
	return ReturnSkeletalPath;
}

UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "CustomEvent")
void ACPP_Villager::ReturnToIdle()
{
	ACPP_Villager::ChangeJob_Implementation(FName("Idle"));
}
void ACPP_Villager::ReturnToDefaultBT_Implementation()
{
	ACPP_Villager::ChangeJob_Implementation(FName("Idle"));
}

UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "CustomEvent")
void ACPP_Villager::PlayVillagerAnim(UAnimMontage* Montage, float length)
{
	Mesh->GetAnimInstance()->Montage_Play(Montage, 1.0f);
	//On completed delegate
	auto MontageCompleteDelegate = ACPP_Villager::Mesh->GetAnimInstance()->Montage_GetBlendingOutDelegate();
	//Mesh->GetAnimInstance()->Montage_SetBlendingOutDelegate(MontageCompleteDelegate, Montage);
	
}

void ACPP_Villager::Action_Implementation(AActor* ParamActor)
{	
	if (ParamActor) {
		Target_Ref = ParamActor;
		if (ParamActor->Tags[0].IsValid()) {
			ACPP_Villager::ChangeJob_Implementation(FName(ParamActor->Tags[0].ToString()));
			//Add after completing GI
			//GetWorld()->GetGameInstance()
		}
	}
}

void ACPP_Villager::ChangeJob_Implementation(FName NewJob)
{
	New_Job = NewJob;
	UDataTable* DT_JobData = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/CppBPs/CPPDT_Jobs.CPPDT_Jobs'"));
	FST_Jobs* Row01 = DT_JobData->FindRow<FST_Jobs>(New_Job, "");
	if (Tags.Find(New_Job) == -1) {
		TArray<FName> NewArray;
		NewArray.Add(New_Job);
		Tags = NewArray;
		this->ResetJobState();
		//stream manager ready
		auto& StreamManager = UAssetManager::Get().GetStreamableManager();
		//sequence 00
		sop_BehaviorTree.SetPath(Row01->BehaviourTree->GetPathName());
		StreamManager.RequestAsyncLoad(sop_BehaviorTree,
			FStreamableDelegate::CreateUObject(this, &ACPP_Villager::OnLoadComplete_BehaviorTree));
		//sequence 01
		sop_WorkAnim.SetPath(Row01->WorkAnim->GetPathName());
		StreamManager.RequestAsyncLoad(sop_WorkAnim, 
			FStreamableDelegate::CreateUObject(this, &ACPP_Villager::OnLoadComplete_AnimMontage));
		//sequence 02
		sop_Hat.SetPath(Row01->Hat->GetPathName());
		StreamManager.RequestAsyncLoad(sop_Hat,
			FStreamableDelegate::CreateUObject(this, &ACPP_Villager::OnLoadComplete_HatSkeletal));
		
		//sequence 03
		sop_Tool.SetPath(Row01->Tools->GetPathName());
		StreamManager.RequestAsyncLoad(sop_Tool,
			FStreamableDelegate::CreateUObject(this, &ACPP_Villager::OnLoadComplete_ToolSkeletal));
	}
}

//async complete delegate functions
void ACPP_Villager::OnLoadComplete_BehaviorTree()
{
	AAIController* AIController = Cast<AAIController>(AIControllerClass);
	AIController->RunBehaviorTree(Cast<UBehaviorTree>(sop_BehaviorTree.ResolveObject()));
	ActiveBehavior = Cast<UBehaviorTree>(sop_BehaviorTree.ResolveObject());
	if (Target_Ref) {
		AIController->GetBlackboardComponent()->GetValueAsObject("Target");
	}
}
void ACPP_Villager::OnLoadComplete_AnimMontage() {
	Work_Anim = Cast<UAnimMontage>(sop_WorkAnim.ResolveObject());
}
void ACPP_Villager::OnLoadComplete_HatSkeletal() {
	Hat->SetSkeletalMesh(Cast<USkeletalMesh>(sop_Hat.ResolveObject()));
	Hat->SetVisibility(true);
}
void ACPP_Villager::OnLoadComplete_ToolSkeletal() {
	Target_Tool = Cast<UStaticMesh>(sop_Tool.ResolveObject());
}

void ACPP_Villager::PlayWorkAnim_Implementation(float Delay)
{
	this->PlayVillagerAnim(Work_Anim, Delay);
	Tool->SetStaticMesh(Target_Tool);
	Tool->SetVisibility(true);
}
