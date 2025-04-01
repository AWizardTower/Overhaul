// Fill out your copyright notice in the Description page of Project Settings.


#include "Overhaul/Public/CheckModule/QuestionDecal.h"

#include "Components/DecalComponent.h"


// Sets default values
AQuestionDecal::AQuestionDecal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetCollisionProfileName(TEXT("BlockAll"));

	Decal = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));
	Decal->SetupAttachment(RootComponent);
	Decal->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	HighLightDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("Hightlight_Decal"));
	HighLightDecal->SetupAttachment(RootComponent);
	HighLightDecal->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	HighLightDecal->SetHiddenInGame(true);
}

// Called when the game starts or when spawned
void AQuestionDecal::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AQuestionDecal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AQuestionDecal::ProcessChosen(bool IsChosen)
{
	if (IsChosen) SetActorHiddenInGame(false);
	else
	{
		SetActorHiddenInGame(true);
	}
}

int32 AQuestionDecal::ProcessHit(UCheckModuleManager* CheckModule)
{
	if (IsValid) return -1;
	IsValid = true;

	CheckModule->AddScore();

	BoxCollision->SetCollisionProfileName(TEXT("NoCollision"));
	if (HighLightDecal)
	{
		HighLightDecal->SetHiddenInGame(false);
	}
	return QuestionIndex;
}
