// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CheckModuleManager.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "QuestionDecal.generated.h"

UCLASS(Blueprintable)
class OVERHAUL_API AQuestionDecal : public AActor
{
private:
	GENERATED_BODY()

	bool IsValid = false;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UDecalComponent* Decal;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UDecalComponent* HighLightDecal;

public:
	// Sets default values for this actor's properties
	AQuestionDecal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void ProcessChosen(bool IsChosen);

	UPROPERTY(EditAnywhere, Category="CustomSetting")
	int32 QuestionIndex;

	UFUNCTION(BlueprintCallable, Category="Decal")
	int32 ProcessHit(UCheckModuleManager* CheckModule);
};
