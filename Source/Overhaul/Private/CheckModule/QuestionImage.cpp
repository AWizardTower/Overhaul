// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckModule/QuestionImage.h"
#include "EngineUtils.h"

// Sets default values
AQuestionImage::AQuestionImage()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AQuestionImage::OnBoxBeginOverlap);
}

// Called when the game starts or when spawned
void AQuestionImage::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AQuestionImage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AQuestionImage::ProcessChosen(bool IsChosen)
{
	if (IsChosen) SetActorHiddenInGame(false);
	else SetActorHiddenInGame(true);
}

struct FShowUIParams
{
	int32 QuestionIndex;
	AActor* Actor;
	bool IsJudgmentQuestion = false;
};

void AQuestionImage::OnBoxBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	UWorld* World = GetWorld();
	UE_LOG(LogTemp, Log, TEXT("Found Blueprint Instance:"));
	if (!World) return;
	UClass* UIBlueprint = LoadObject<UClass>(nullptr,TEXT("/Script/Engine.Blueprint'/Game/Trail/CheckModule/Questions/QuestionImage/BP_ShowUI.BP_ShowUI_C'"));
	if (!UIBlueprint) return;

	for (TActorIterator<AActor> It(World, UIBlueprint); It; ++It)
	{
		AActor* UIBlueprintInstance = *It;
		if (UIBlueprintInstance)
		{
			UFunction* ShowUIFunction = UIBlueprintInstance->FindFunction("ShowUI");
			if (ShowUIFunction)
			{
				FShowUIParams Params;
				Params.Actor = Cast<AActor>(this);
				Params.QuestionIndex = QuestionIndex;
				Params.IsJudgmentQuestion = true;
				UIBlueprintInstance->ProcessEvent(ShowUIFunction, &Params);
			}
		}
	}
}

int32 AQuestionImage::ProcessHit(UCheckModuleManager* CheckModule)
{
	this->Destroy();
	CheckModule->AddScore();
	return QuestionIndex;
}
