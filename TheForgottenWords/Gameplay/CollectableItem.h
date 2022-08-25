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


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Rendering)
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USceneComponent* DefaultSceneRoot;


	//All the uproperty that I will be using for the collectible item.
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FText Title;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FText Description;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool bTakeable = false;


	UPROPERTY(EditAnywhere, Category = "Inspection")
		UCurveFloat* CurveFloat;

	UPROPERTY(EditAnywhere, Category = "Inspection")
		float PlayRate = 1.0f;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "bTakeable"))
		USoundBase* TakeSound;

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

	float FadeIn;

	FOnTimelineFloat InterpFunction;
	FVector ObjectLoc;
	FRotator ObjectRot;

	FRotator NewRot;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
