// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"

#include "Blueprint/UserWidget.h"

#include "PlayerCharacter.generated.h"


UCLASS()
class THEFORGOTTENWORDS_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* CameraView;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USphereComponent* ViewLocation;

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


	void DisplayWidget(TSubclassOf<UUserWidget> WidgetClass, UUserWidget* Widget);

	UPROPERTY(EditAnywhere, Category = "CameraManager")
		TSubclassOf<UCameraShakeBase> CameraShake;

	bool bDisplayed = false;

	UFUNCTION()
		void OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
		AActor* Linetrace(float TraceDistance);
		AActor* Linetrace_Implementation(float TraceDistance);



private:

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int SelectedIndex = 1;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
