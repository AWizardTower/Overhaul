// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CheckModuleManager.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "QuestionMaterialChange.generated.h"

UCLASS()
class OVERHAUL_API AQuestionMaterialChange : public AActor
{
	GENERATED_BODY()

	bool IsValid = false;
	UMaterialInterface* PrimaryMaterial;
	
	UPROPERTY(VisibleAnywhere, Category="Component")
	UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, Category="Component")
	UStaticMeshComponent* Model;

	UPROPERTY(VisibleAnywhere, Category="Component")
	UDecalComponent* Decal;

public:
	// Sets default values for this actor's properties
	AQuestionMaterialChange();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ProcessChosen(bool IsChosen);
	int32 ProcessHit(UCheckModuleManager* CheckModule);

	UPROPERTY(EditAnywhere, Category="CustomSetting")
	int32 QuestionIndex;

	UPROPERTY(EditAnywhere, Category="CustomSetting")
	UMaterialInstance* WrongMaterial;
};
