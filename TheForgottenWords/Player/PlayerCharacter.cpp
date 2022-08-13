// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "DrawDebugHelpers.h"
#include <TheForgottenWords/Gameplay/InteractableItem.h>
#include <TheForgottenWords/Gameplay/CollectableItem.h>


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->MaxWalkSpeed = (250.0f);


	//FirstPerson CameraSetup
	CameraView = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera View"));
	CameraView->SetupAttachment(RootComponent);
	CameraView->bUsePawnControlRotation = true;
	CameraView->SetRelativeLocation(FVector(0.0f, 0.0f, 70.0f));
	CameraView->SetFieldOfView(100.0f);

	ViewLocation = CreateDefaultSubobject<USphereComponent>(TEXT("ViewLocation"));
	ViewLocation->SetupAttachment(CameraView);
	ViewLocation->InitSphereRadius(10.0f);
	ViewLocation->SetRelativeLocation(FVector(45.0f, 0.0f, 1.0f));

	AutoPossessPlayer = EAutoReceiveInput::Player0;


}

void APlayerCharacter::OnBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnBeginOverlap);
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurveTimeline.TickTimeline(DeltaTime);

	AActor* AimedActor = Linetrace(125);

	if (AimedActor)
	{

		if (AInteractableItem* pInteractableCastingResult = Cast<AInteractableItem>(AimedActor))
		{
			SelectedIndex = 1;
		}
		else if(ACollectableItem* pCollectableCastingResult = Cast<ACollectableItem>(AimedActor))
		{

			SelectedIndex = 0;

		}
		DisplayWidget(Interaction_Widget_Class, Interaction_Widget);
	}

	

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::TurnUp);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::TurnLeft);

	//Interact PlayerInputComponent
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::InteractPressed);

	//Move Forward and move right PlayerInputComponent
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);


}


void APlayerCharacter::MoveForward(float axis)
{
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, axis);
	APlayerCharacter::PlayCameraShake(axis);

}

void APlayerCharacter::MoveRight(float Axis)
{
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Axis);
	APlayerCharacter::PlayCameraShake(Axis);

}

void APlayerCharacter::InteractPressed()
{

	TargetActor = Linetrace(400);

	if (TargetActor)
	{
		if (!bZoom) {

			if (Cast<ACollectableItem>(TargetActor))
			{
				
				if (CurveFloat)
				{
					PlayInspectionAnimation(TargetActor);

				}


			}

		}
		else 
		{
			bZoom = false;
			CurveTimeline.Reverse();
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);


		}

	}
}

void APlayerCharacter::PlayCameraShake(float Scale)
{

	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(CameraShake, Scale);

}

void APlayerCharacter::TimelineProgress(float Value)
{

	FadeIn = Value;
	FVector NewLocation = FMath::Lerp(ObjectLoc, ViewLocation->GetComponentLocation(), FadeIn);
	FRotator NewRotation = FMath::Lerp(ObjectRot, NewRot, FadeIn);
	TargetActor->SetActorLocationAndRotation(NewLocation, NewRotation);
	

}

void APlayerCharacter::TurnLeft(float Value)
{

	if (bZoom)
	{
		const FRotator YawRotation(0.0f, (Value * -1.0f), 0.0f);
		FRotator CombinedRotators = YawRotation + TargetActor->GetActorRotation();
		NewRot = CombinedRotators;
		TargetActor->SetActorRotation(CombinedRotators);

	}
	else
	{

		AddControllerYawInput(Value);

	}
		


}

void APlayerCharacter::TurnUp(float Value)
{
	if (bZoom)
	{
		const FRotator YawRotation(Value, 0.0f, 0.0f);
		FRotator CombinedRotators = YawRotation + TargetActor->GetActorRotation();
		TargetActor->SetActorRotation(CombinedRotators);
	}
	else
	{

		AddControllerPitchInput(Value);

	}


}


void APlayerCharacter::DisplayWidget(TSubclassOf<UUserWidget> WidgetClass, UUserWidget* Widget)
{
	if (IsValid(WidgetClass))
	{
		Widget = CreateWidget(GetWorld(), WidgetClass);

		if (Widget != nullptr)
		{
			Widget->AddToViewport();
		}

	}
}

AActor* APlayerCharacter::Linetrace_Implementation(float TraceDistance)
{

	FVector Location;
	FRotator Rotation;
	FHitResult HitResult;

	GetController()->GetPlayerViewPoint(Location, Rotation);

	FVector StartPoint = Location;
	FVector EndPoint = StartPoint + (Rotation.Vector() * TraceDistance);

	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECC_Visibility, TraceParams);

	if (bHit) 
	{
		return HitResult.GetActor();
	}
	return nullptr;

}

void APlayerCharacter::PlayInspectionAnimation(AActor* Target)
{
	bZoom = true;
	InterpFunction.BindUFunction(this, FName("TimelineProgress"));

	CurveTimeline.AddInterpFloat(CurveFloat, InterpFunction);
	CurveTimeline.SetPlayRate(PlayRate);

	ObjectLoc = Target->GetActorLocation();
	ObjectRot = Target->GetActorRotation();

	CurveTimeline.PlayFromStart();
	GetCharacterMovement()->DisableMovement();
}






