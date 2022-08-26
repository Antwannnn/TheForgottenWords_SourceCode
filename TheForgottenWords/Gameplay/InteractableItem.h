// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundAttenuation.h"
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

	FVector StartLoc;

	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundBase* ItemSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundAttenuation* SoundAttenuation;

	bool bDelay = false;

	UFUNCTION()
		void TimerMethod();

	UFUNCTION()
		void DisplayTextWidget();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Timeline")
		bool ApplyTransform;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "ApplyTransform"), Category = "Timeline")
		FTransform ObjectTransform;

	UPROPERTY(EditAnywhere, Category = "Timeline", meta = (EditCondition = "ApplyTransform"))
		UCurveFloat* CurveFloat;

	UPROPERTY(EditAnywhere, Category = "Timeline", meta = (EditCondition = "ApplyTransform"))
		float Rate;

	UPROPERTY(EditAnywhere, Category = "UI HUD")
		TSubclassOf<UUserWidget> InteractionWidgetClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "UI HUD")
		FText Text;

	FTimeline CurveTimeline;

	FTimerHandle TH_WidgetDelayManager;

	UInteractionUI* InteractionWidget;

	UPROPERTY(EditAnywhere, Category = "Timeline", meta = (EditCondition = "ApplyTransform"))
		bool DoOnce;

	bool bDoOnce;

	FVector EndLoc;

	FRotator StartRot;

	FRotator EndRot;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};