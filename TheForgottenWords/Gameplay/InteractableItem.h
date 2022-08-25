// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include <TheForgottenWords/UI/InteractionUI.h>

#include "Blueprint/UserWidget.h"

#include "InteractableItem.generated.h"

class UCurveFloat;

UCLASS()
class THEFORGOTTENWORDS_API AInteractableItem : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractableItem();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Rendering)
		UStaticMeshComponent* Mesh;

	UFUNCTION()
		void TimelineProgress(float Value);

	UFUNCTION(BlueprintCallable)
		void PlayTransformTimeline();

	UPROPERTY(EditAnywhere, meta = (EditCondition = "ApplyTransform"), Category = "Timeline")
		FTransform ObjectTransform;

	FTimerHandle TH_WidgetDelayManager;

	UPROPERTY(EditAnywhere, Category = "UI HUD")
		TSubclassOf<UUserWidget> InteractionWidgetClass;

	UInteractionUI* InteractionWidget;

	bool bDelay = false;

	UFUNCTION()
		void TimerMethod();

	void DisplayTextWidget();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "UI HUD")
		FText Text;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Timeline")
		bool ApplyTransform;

	FTimeline CurveTimeline;

	UPROPERTY(EditAnywhere, Category = "Timeline", meta = (EditCondition = "ApplyTransform"))
		UCurveFloat* CurveFloat;

	UPROPERTY(EditAnywhere, Category = "Timeline", meta = (EditCondition = "ApplyTransform"))
		float Rate;

	UPROPERTY(EditAnywhere, Category = "Timeline", meta = (EditCondition = "ApplyTransform"))
		bool DoOnce;
	bool bDoOnce;

	FVector StartLoc;

	FVector EndLoc;

	FRotator StartRot;

	FRotator EndRot;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};