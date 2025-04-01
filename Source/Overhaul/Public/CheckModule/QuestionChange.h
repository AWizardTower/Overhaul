// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CheckModuleManager.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "QuestionChange.generated.h"

UCLASS(Blueprintable)
class OVERHAUL_API AQuestionChange : public AActor
{
	GENERATED_BODY()
	FString ModelName;
	bool IsValid = false;
	UStaticMesh* PrimaryModel;

public:
	// Sets default values for this actor's properties
	AQuestionChange();

	UPROPERTY(VisibleAnywhere,Category="Components");
	UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UStaticMeshComponent* Model;

	UPROPERTY(EditAnywhere, Category="CustomSettinng")
	int32 QuestionIndex;
	
	UPROPERTY(EditAnywhere, Category="CustomSettinng")
	UStaticMesh* WrongModel;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ProcessChosen(bool IsChosen);

	UFUNCTION(BlueprintCallable, Category="ModelChange")
	int32 ProcessHit(UCheckModuleManager* CheckMudule);
};
