// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Components/SceneComponent.h"


#include "CollectableItem.generated.h"

UCLASS()
class THEFORGOTTENWORDS_API ACollectableItem : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACollectableItem();

	//All the uproperty that I will be using for the collectible item.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Inspection)
		FText Title;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Inspection)
		FText Description;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Inspection)
		bool bTakeable = false;

	UPROPERTY(EditAnywhere, Category = Inspection, meta = (EditCondition = "bTakeable", EditConditionHides))
		USoundBase* TakeSound;

	UPROPERTY(EditAnywhere, Category = Inspection)
		UCurveFloat* CurveFloat;

	UPROPERTY(EditAnywhere, Category = Inspection)
		float PlayRate = 1.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USceneComponent* DefaultSceneRoot;

	UFUNCTION(BlueprintCallable)
		void PlayTakeSound();

	UFUNCTION()
		void TimelineProgress(float Value);

	UFUNCTION()
		void PlayInspectionAnimation(FVector Location);

	FVector ViewLocation;

	FOnTimelineEvent FinishedEvent;

	UFUNCTION()
		void TurnUp(float Value);

	UFUNCTION()
		void TurnLeft(float Value);

	FTimeline CurveTimeline;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	float FadeIn;

	FOnTimelineFloat InterpFunction;
	FVector ObjectLoc;
	FRotator ObjectRot;
	FRotator NewRot;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
