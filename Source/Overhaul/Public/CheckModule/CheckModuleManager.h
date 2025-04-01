// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CheckModuleManager.generated.h"

// type：贴花、角度调整、模型替换、图片
UENUM()
enum EQuestionType
{
	Decal, Rotate, ModelChange, Image, MaterialChange
};

class Question
{
public:
	EQuestionType Type;
	AActor* Actor;
};

USTRUCT(BlueprintType)
struct FReturnResult
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite)
	int32 QuestionIndex = -1;

	UPROPERTY(BlueprintReadWrite)
	bool IsJudgmentQuestion = false;
};


/**
 * 
 */
UCLASS(Blueprintable)
class OVERHAUL_API UCheckModuleManager : public UObject
{
	GENERATED_BODY()

private:
	int32 Score = 0;
	int32 Time = 30; //minutes

	TArray<Question*> QuestionList;

public:
	UCheckModuleManager();
	~UCheckModuleManager();

	void GatherQuestions(); // 从场景中获取故障
	void AddQuestion(AActor* Actor, EQuestionType Type);

	UFUNCTION(BlueprintCallable, Category="CheckModule")
	void ProcessQuestions(int QuestionNum);

	UFUNCTION(BlueprintCallable, Category="CheckModule")
	void AddScore()
	{
		Score++;
		UE_LOG(LogTemp, Warning, TEXT("Score: %d"), GetModuleScore());
	}

	UFUNCTION(BlueprintCallable, Category="CheckModule")
	int32 GetModuleScore() { return Score; }

	UFUNCTION(BlueprintCallable, Category="CheckModule")
	FReturnResult ProcessLineRayResult(AActor* Actor);
};
