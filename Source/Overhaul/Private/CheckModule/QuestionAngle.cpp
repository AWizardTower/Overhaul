// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckModule/QuestionAngle.h"

// Sets default values
AQuestionAngle::AQuestionAngle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Model = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Model"));

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetCollisionProfileName(TEXT("BlockAll"));

	UStaticMesh* CubeMesh = LoadObject<UStaticMesh>(nullptr,TEXT("/Engine/BasicShapes/Cube"));
	if (CubeMesh)
	{
		Model->SetStaticMesh(CubeMesh);
	}
}

void AQuestionAngle::ProcessChosen(bool IsChosen)
{
	if (IsChosen)
	{
		this->SetActorRelativeRotation(WrongRotateAngle);
		this->SetActorRelativeLocation(WrongPosition);
		IsValid = true;
	}
	else
	{
		this->SetActorRelativeRotation(CorrectRotateAngle);
		this->SetActorRelativeLocation(CorrectPosition);
	}
}

int32 AQuestionAngle::ProcessHit(UCheckModuleManager* CheckModule)
{
	if (!IsValid) return -1;
	IsValid = false;

	CheckModule->AddScore();
	Model->SetRenderCustomDepth(true);
	return QuestionIndex;
}

void AQuestionAngle::SaveWrongAngle()
{
	WrongRotateAngle = Model->GetRelativeRotation();
	WrongPosition = Model->GetRelativeLocation();
}

void AQuestionAngle::SaveCorrectAngle()
{
	CorrectRotateAngle = Model->GetRelativeRotation();
	CorrectPosition = Model->GetRelativeLocation();
}

// Called when the game starts or when spawned
void AQuestionAngle::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AQuestionAngle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
