// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <TheForgottenWords/GameplayUtils.h>
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include <TheForgottenWords/Gameplay/InteractableItem.h>
#include <TheForgottenWords/Gameplay/CollectableItem.h>
#include <TheForgottenWords/Libraries//GameplayEvents.h>
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Components/TimelineComponent.h"

#include "Blueprint/UserWidget.h"

#include "PlayerCharacter.generated.h"

UCLASS(Blueprintable)
class THEFORGOTTENWORDS_API APlayerCharacter : public ACharacter//, public IGameplayUtils
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* CameraView;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inspection")
		USphereComponent* ViewLocation;

	UPROPERTY(EditAnywhere, Category = "Inspection")
		UCurveFloat* CurveFloat;

	UPROPERTY(EditAnywhere, Category = "Inspection")
		float PlayRate = 1.0f;

	UPROPERTY(EditAnywhere, Category = "UI HUD")
		TSubclassOf<UUserWidget> Interaction_Widget_Class;

	UUserWidget* Interaction_Widget;

	UFUNCTION()
		void MoveForward(float axis);

	UFUNCTION()
		void MoveRight(float Axis);

	UFUNCTION()
		void InteractPressed();


	UFUNCTION()
		void PlayCameraShake(float Scale);

	UFUNCTION()
		void LookRight(float Value);

	UFUNCTION()
		void LookUp(float Value);

	UFUNCTION()
		void Flip();

	UPROPERTY()
		bool bInteracting = false;

	UPROPERTY()
		bool bZoom = false;

	UPROPERTY()
		bool b = true;

	//Flip Flop variable manager

	bool bDisplayed;

	UFUNCTION(BlueprintCallable)
		void ConstructWidget(TSubclassOf<UUserWidget> WidgetClass, UUserWidget* Widget, UWorld* World);

	UPROPERTY(EditAnywhere, Category = "CameraManager")
		TSubclassOf<UCameraShakeBase> CameraShake;

	AActor* TargetActor;

	UFUNCTION()
		void OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int SelectedIndex;

	float FadeIn;

	FTimeline CurveTimeline;
	FOnTimelineFloat InterpFunction;
	FOnTimelineEvent TimelineFinished;

	FVector ObjectLoc;
	FRotator ObjectRot;

	FRotator NewRot;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


};
