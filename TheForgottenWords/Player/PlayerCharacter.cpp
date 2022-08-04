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
	CameraView->SetFieldOfView(100.0f);

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

	AActor* TargetActor = Linetrace(400);

	if (TargetActor)
	{

		if (AInteractableItem* pCastingResult = Cast<AInteractableItem>(TargetActor))
		{
			SelectedIndex = 1;
		}
		else if(ACollectableItem* pCastingResult2 = Cast<ACollectableItem>(TargetActor))
		{

			SelectedIndex = 0;

		}
		DisplayWidget(SelectedIndex, Interaction_Widget_Class, Interaction_Widget);
	}

	

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Turn Up/Right PlayerInputComponent
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

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

	if (AActor* TargetActor = Linetrace(400))
	{
		if (Cast<AInteractableItem>(TargetActor))
		{

		}

	}
}

void APlayerCharacter::PlayCameraShake(float Scale)
{

	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(CameraShake, Scale);

}


void APlayerCharacter::DisplayWidget(int index, TSubclassOf<UUserWidget> WidgetClass, UUserWidget* Widget)
{
	if (IsValid(WidgetClass))
	{
		SelectedIndex = index;
		Widget = CreateWidget(GetWorld(), WidgetClass);

		if (Widget != nullptr)
		{
			Widget->AddToViewport();
		}

	}
}
//DisplayWidget method implementation overloading
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




