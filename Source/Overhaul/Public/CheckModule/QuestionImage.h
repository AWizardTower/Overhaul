// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CheckModuleManager.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "QuestionImage.generated.h"

UCLASS()
class OVERHAUL_API AQuestionImage : public AActor
{
	GENERATED_BODY()
	bool IsValid = false;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UBoxComponent* BoxCollision;

public:
	// Sets default values for this actor's properties
	AQuestionImage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ProcessChosen(bool IsChosen);
	int32 ProcessHit(UCheckModuleManager* CheckModule);

	UPROPERTY(EditAnywhere, Category="CustomSetting")
	int32 QuestionIndex = 0;

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                       const FHitResult& SweepResult);
};
