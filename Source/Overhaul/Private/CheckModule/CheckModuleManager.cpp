// Fill out your copyright notice in the Description page of Project Settings.


#include "Overhaul/Public/CheckModule/CheckModuleManager.h"
#include "Engine/Engine.h"
#include "EngineUtils.h"
#include "CheckModule/QuestionChange.h"
#include "CheckModule/QuestionDecal.h"
#include "CheckModule/QuestionAngle.h"
#include "CheckModule/QuestionImage.h"
#include "CheckModule/QuestionMaterialChange.h"
#include "Materials/MaterialInstanceActor.h"
#include "Math/UnrealMath.h"
#define NUM_PROBLEMS


UCheckModuleManager::UCheckModuleManager()
{
	// 将场景中所有场景清零，恢复飞机的正常样子
	GatherQuestions();
	ProcessQuestions(0);
}

UCheckModuleManager::~UCheckModuleManager()
{
}

void UCheckModuleManager::AddQuestion(AActor* Actor, EQuestionType Type)
{
	Question* NewQuestion = new Question;
	NewQuestion->Actor = Actor;
	NewQuestion->Type = Type;
	QuestionList.Push(NewQuestion);
}

void UCheckModuleManager::GatherQuestions()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Generate Questions"));
	}

	// 从场景中获取所有故障
	UWorld* World = GetWorld();
	if (World)
	{
		// 贴花
		for (TActorIterator<AQuestionDecal> It(World); It; ++It)
		{
			AQuestionDecal* DecalBreak = *It;
			if (DecalBreak)
			{
				AActor* DecalActor = Cast<AActor>(DecalBreak);
				if (DecalActor) AddQuestion(DecalActor, Decal);
			}
		}

		// 角度调整
		for (TActorIterator<AQuestionAngle> It(World); It; ++It)
		{
			AQuestionAngle* AngleBreak = *It;
			if (AngleBreak)
			{
				AActor* AngleActor = Cast<AActor>(AngleBreak);
				if (AngleActor) AddQuestion(AngleActor, Rotate);
			}
		}

		// 模型切换
		for (TActorIterator<AQuestionChange> It(World); It; ++It)
		{
			AQuestionChange* ModelChangeBreak = *It;
			if (ModelChangeBreak)
			{
				AActor* ModelChangeActor = Cast<AActor>(ModelChangeBreak);
				if (ModelChangeActor) AddQuestion(ModelChangeBreak, ModelChange);
			}
		}

		// 题目判断
		for (TActorIterator<AQuestionImage> It(World); It; ++It)
		{
			AQuestionImage* ImageQuestion = *It;
			if (ImageQuestion)
			{
				AActor* ImageActor = Cast<AActor>(ImageQuestion);
				if (ImageQuestion) AddQuestion(ImageActor, Image);
			}
		}

		// 材质改变
		for (TActorIterator<AQuestionMaterialChange> It(World); It; ++It)
		{
			AQuestionMaterialChange* Material = *It;
			if (MaterialChange)
			{
				AActor* MaterialChangeActor = Cast<AActor>(Material);
				if (MaterialChangeActor) AddQuestion(MaterialChangeActor, MaterialChange);
			}
		}
	}
}

TSet<int32> GenerateRandomIntegers(int32 NumToGenerate, int32 MinValue, int32 MaxValue)
{
	TSet<int32> Result;
	if (NumToGenerate < 0 || MaxValue < MinValue)return Result;

	int32 RangeSize = MaxValue - MinValue + 1;
	NumToGenerate = FMath::Min(NumToGenerate, RangeSize);
	while (Result.Num() < NumToGenerate)
	{
		int32 RandomValue = FMath::RandRange(MinValue, MaxValue);
		Result.Add(RandomValue);
	}
	return Result;
}

void UCheckModuleManager::ProcessQuestions(int32 QuestionNum)
{
	//随机获取一定数量的题号
	TSet<int32> ValidIndex = GenerateRandomIntegers(QuestionNum, 0, QuestionList.Num() - 1);
	for (int i = 0; i < QuestionList.Num(); i++)
	{
		Question* Quest = QuestionList[i];
		switch (Quest->Type)
		{
		case Decal:
			{
				AQuestionDecal* DecalActor = Cast<AQuestionDecal>(Quest->Actor);
				if (DecalActor) DecalActor->ProcessChosen(ValidIndex.Contains(i));
			}
			break;

		case Rotate:
			{
				AQuestionAngle* AngleActor = Cast<AQuestionAngle>(Quest->Actor);
				if (AngleActor) AngleActor->ProcessChosen(ValidIndex.Contains(i));
			}
			break;

		case ModelChange:
			{
				AQuestionChange* ModelChangeActor = Cast<AQuestionChange>(Quest->Actor);
				if (ModelChangeActor) ModelChangeActor->ProcessChosen(ValidIndex.Contains(i));
			}
			break;
		case Image:
			{
				AQuestionImage* ImageActor = Cast<AQuestionImage>(Quest->Actor);
				if (ImageActor) ImageActor->ProcessChosen(ValidIndex.Contains(i));
			}
		case MaterialChange:
			{
				AQuestionMaterialChange* MaterialChangeActor = Cast<AQuestionMaterialChange>(Quest->Actor);
				if (MaterialChangeActor) MaterialChangeActor->ProcessChosen(ValidIndex.Contains(i));
			}
		}
	}
}

FReturnResult UCheckModuleManager::ProcessLineRayResult(AActor* Actor)
{
	FReturnResult Result;
	AQuestionDecal* Decal = Cast<AQuestionDecal>(Actor);
	if (Decal)
	{
		Result.QuestionIndex = Decal->ProcessHit(this);
		return Result;
	}

	AQuestionAngle* Angel = Cast<AQuestionAngle>(Actor);
	if (Angel)
	{
		Result.QuestionIndex = Angel->ProcessHit(this);
		return Result;
	}

	AQuestionChange* ModelChange = Cast<AQuestionChange>(Actor);
	if (ModelChange)
	{
		Result.QuestionIndex = ModelChange->ProcessHit(this);
		return Result;
	}

	AQuestionImage* ImageJudge = Cast<AQuestionImage>(Actor);
	if (ImageJudge)
	{
		Result.QuestionIndex = ImageJudge->ProcessHit(this);
		Result.IsJudgmentQuestion = true;
		return Result;
	}

	AQuestionMaterialChange* Material = Cast<AQuestionMaterialChange>(Actor);
	if (Material)
	{
		Result.QuestionIndex = Material->ProcessHit(this);
		return Result;
	}

	return Result;
}
