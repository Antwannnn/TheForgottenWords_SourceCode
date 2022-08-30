// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "DrawDebugHelpers.h"



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
	ViewLocation->SetRelativeLocation(FVector(30.0f, 0.0f, 1.0f));

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

	if (!bZoom)
	{
		TargetActor = UGameplayEvents::LinetraceByChannel(125, GetWorld(), GetController());

		if (TargetActor)
		{
			if (Cast<AInteractableItem>(TargetActor))
			{
				SelectedIndex = 1;
				ConstructWidget(Interaction_Widget_Class, Interaction_Widget, GetWorld());
			}
			else if (Cast<ACollectableItem>(TargetActor))
			{
				SelectedIndex = 0;
				ConstructWidget(Interaction_Widget_Class, Interaction_Widget, GetWorld());
			}
		}
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::LookRight);

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
	if (!bInteracting)
	{
		if (!bZoom)
		{
			TargetActor = UGameplayEvents::LinetraceByChannel(125, GetWorld(), GetController());

			if (ACollectableItem* CollectableItemCheck = Cast<ACollectableItem>(TargetActor))
			{
				bZoom = true;
				bInteracting = true;
				GetCharacterMovement()->DisableMovement();
				CollectableItemCheck->FinishedEvent.BindUFunction(this, "Flip");
				CollectableItemCheck->PlayInspectionAnimation(ViewLocation->GetComponentLocation());

			}
			else if (AInteractableItem* InteractableItemCheck = Cast<AInteractableItem>(TargetActor))
			{
				if (!InteractableItemCheck->bDelay)
				{
					InteractableItemCheck->DisplayTextWidget();
					InteractableItemCheck->PlayTransformTimeline();
				}

			}
		}
		else
		{
			if (ACollectableItem* CollectableItemCheck = Cast<ACollectableItem>(TargetActor))
			{
				if (CollectableItemCheck->bTakeable)
				{
					CollectableItemCheck->PlayTakeSound();
					GetWorld()->DestroyActor(TargetActor);
					Flip();
				}
				else
				{
					CollectableItemCheck->CurveTimeline.Reverse();
				}
			}
		}
	}
}

void APlayerCharacter::PlayCameraShake(float Scale)
{
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(CameraShake, Scale);
}

void APlayerCharacter::LookRight(float Value)
{
	if (bZoom)
	{
		if (ACollectableItem* CollectableItemCheck = Cast<ACollectableItem>(TargetActor))
		{
			CollectableItemCheck->TurnLeft(Value);
		}
	}
	else
	{
		AddControllerYawInput(Value);
	}

}

void APlayerCharacter::LookUp(float Value)
{
	if (bZoom)
	{
		if (ACollectableItem* CollectableItemCheck = Cast<ACollectableItem>(TargetActor))
		{
			CollectableItemCheck->TurnUp(Value);
		}
	}
	else
	{
		AddControllerPitchInput(Value);
	}


}

void APlayerCharacter::Flip()
{
	if (b)
	{
		b = false;
		bInteracting = false;
	}
	else
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		bInteracting = false;
		bZoom = false;
		b = true;
	}
}

void APlayerCharacter::ConstructWidget(TSubclassOf<UUserWidget> WidgetClass, UUserWidget* Widget, UWorld* World)
{
	if (IsValid(WidgetClass))
	{
		Widget = CreateWidget(World, WidgetClass);

		if (Widget != nullptr)
		{
			Widget->AddToViewport();
		}
	}
}