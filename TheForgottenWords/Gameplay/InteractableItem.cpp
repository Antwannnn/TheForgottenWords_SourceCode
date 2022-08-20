// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableItem.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AInteractableItem::AInteractableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

}

// Called when the game starts or when spawned
void AInteractableItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurveTimeline.TickTimeline(DeltaTime);

}

void AInteractableItem::TimelineProgress(float Value)
{

	FVector NewLocation = FMath::Lerp(StartLoc, EndLoc, Value);
	FRotator NewRotator = FMath::Lerp(StartRot, EndRot, Value);
	SetActorLocation(NewLocation);
	SetActorRotation(NewRotator);

}

void AInteractableItem::PlayAnimationTimeline()
{
	if (CurveFloat)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("TimelineProgress"));

		CurveTimeline.AddInterpFloat(CurveFloat, TimelineProgress);
		CurveTimeline.SetLooping(true);
		CurveTimeline.SetPlayRate(Rate);

		StartLoc = EndLoc = GetActorLocation();
		EndLoc.X += ObjectTransform.GetLocation().X;
		EndLoc.Y += ObjectTransform.GetLocation().Y;
		EndLoc.Z += ObjectTransform.GetLocation().Z;

		StartRot = EndRot = GetActorRotation();

		FRotator ToRotator = (FRotator)ObjectTransform.GetRotation();

		EndRot.Pitch += ToRotator.Pitch;
		EndRot.Yaw += ToRotator.Yaw;
		EndRot.Roll += ToRotator.Roll;

		CurveTimeline.PlayFromStart();
	}
}

void AInteractableItem::ConstructWidget()
{

	if (IsValid(InteractionWidgetClass))
	{

		InteractionWidget = Cast<UInteractionUI>(CreateWidget(GetWorld(), InteractionWidgetClass));
		InteractionWidget->TextContent = Text;

		if (InteractionWidget != nullptr)
		{
			InteractionWidget->AddToViewport();
		}

		
	}

}



