// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckModule/QuestionChange.h"

// Sets default values
AQuestionChange::AQuestionChange()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetCollisionProfileName(TEXT("BlockAll"));
	
	Model = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Model"));
	RootComponent = Model;
	UStaticMesh* CubeMesh = LoadObject<UStaticMesh>(nullptr,TEXT("/Engine/BasicShapes/Cube"));
	if (CubeMesh)
	{
		Model->SetStaticMesh(CubeMesh);
	}
}

// Called when the game starts or when spawned
void AQuestionChange::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AQuestionChange::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AQuestionChange::ProcessChosen(bool IsChosen)
{
	if (IsChosen)
	{
		PrimaryModel = Model->GetStaticMesh();
		if (WrongModel)
		{
			Model->SetStaticMesh(WrongModel);
		}
		this->IsValid = true;
	}
	else
	{
		if (PrimaryModel) Model->SetStaticMesh(PrimaryModel);
	}
}

int32 AQuestionChange::ProcessHit(UCheckModuleManager* CheckModule)
{
	if (!IsValid) return -1;
	IsValid = false;

	CheckModule->AddScore();
	Model->SetRenderCustomDepth(true);
	return QuestionIndex;
}
