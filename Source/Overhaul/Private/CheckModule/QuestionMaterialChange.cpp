// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckModule/QuestionMaterialChange.h"

#include "Components/DecalComponent.h"

// Sets default values
AQuestionMaterialChange::AQuestionMaterialChange()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetCollisionProfileName(TEXT("BlockAll"));

	Model = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Model"));
	UStaticMesh* CubeMesh = LoadObject<UStaticMesh>(nullptr,TEXT("/Engine/BasicShapes/Cube"));
	if (CubeMesh)
	{
		Model->SetStaticMesh(CubeMesh);
	}

	Decal = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));
	Decal->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	Decal->SetHiddenInGame(true);
}

// Called when the game starts or when spawned
void AQuestionMaterialChange::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AQuestionMaterialChange::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AQuestionMaterialChange::ProcessChosen(bool IsChosen)
{
	if (IsChosen && WrongMaterial)
	{
		IsValid = true;
		PrimaryMaterial = Model->GetStaticMesh()->GetMaterial(0);
		Model->SetMaterial(0, WrongMaterial);
	}
	else
	{
		if (PrimaryMaterial) Model->SetMaterial(0, PrimaryMaterial);
	}
}

int32 AQuestionMaterialChange::ProcessHit(UCheckModuleManager* CheckModule)
{
	if (!IsValid) return -1;
	CheckModule->AddScore();
	Model->SetRenderCustomDepth(true);
	Decal->SetHiddenInGame(false);
	return QuestionIndex;
}
