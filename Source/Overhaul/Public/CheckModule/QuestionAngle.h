// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CheckModuleManager.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "QuestionAngle.generated.h"

UCLASS(Blueprintable)
class OVERHAUL_API AQuestionAngle : public AActor
{
private:
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere,Category="BoxCollision")
	UBoxComponent* BoxCollision;
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	UStaticMeshComponent* Model;

	// 如果该问题被选中，则IsValid为true，同时，该问题被发现后，IsValid改为false
	UPROPERTY(VisibleAnywhere, Category="CustomSetting")
	bool IsValid = false;

public:
	// Sets default values for this actor's properties
	AQuestionAngle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void SetModelRotation(FRotator Rotation) { Model->SetRelativeRotation(Rotation); }
	void ProcessChosen(bool IsChosen);
	int32 ProcessHit(UCheckModuleManager* CheckModule);

	UPROPERTY(EditAnywhere, Category="CustomSetting")
	int32 QuestionIndex;

	UPROPERTY(VisibleAnywhere, Category="CustomSetting")
	FRotator CorrectRotateAngle;

	UPROPERTY(VisibleAnywhere, Category="CustomSetting")
	FVector CorrectPosition;

	UPROPERTY(VisibleAnywhere, Category="CustomSetting")
	FRotator WrongRotateAngle;

	UPROPERTY(VisibleAnywhere, Category="CustomSetting")
	FVector WrongPosition;

	UFUNCTION(Blueprintable, CallInEditor, Category="CustomSetting")
	void SaveCorrectAngle();

	UFUNCTION(Blueprintable, CallInEditor, Category="CustomSetting")
	void SaveWrongAngle();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
