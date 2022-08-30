// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractableItem.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"


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

void AInteractableItem::PlayTransformTimeline()
{
	if (CurveFloat)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("TimelineProgress"));

		CurveTimeline.AddInterpFloat(CurveFloat, TimelineProgress);
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

		if (DoOnce)
		{
			if(!bDoOnce)
			{
				CurveTimeline.SetTimelineFinishedFunc(FinishedEvent);
				bDoOnce = true;
				CurveTimeline.PlayFromStart();
				UGameplayStatics::PlaySoundAtLocation(this, ItemSound, StartLoc, .5f, 1, 0, SoundAttenuation);
			}
			
		}
		else
		{
			CurveTimeline.PlayFromStart();
			UGameplayStatics::PlaySoundAtLocation(this, ItemSound, StartLoc, .5f, 1, 0, SoundAttenuation);
		}



	}
}

void AInteractableItem::DisplayTextWidget()
{

	if (IsValid(InteractionWidgetClass))
	{
		InteractionWidget = Cast<UInteractionUI>(CreateWidget(GetWorld(), InteractionWidgetClass));
		if (!Text.EqualTo(FText::FromString("")))
		{
			InteractionWidget->TextContent = Text;

			if (InteractionWidget != nullptr)
			{
				bDelay = true;
				InteractionWidget->AddToViewport();
				GetWorld()->GetTimerManager().SetTimer(TH_DelayManager, this, &AInteractableItem::TimerMethod, Delay, false);

			}
		}


	}

}
void AInteractableItem::TimerMethod()
{
	if (InteractionWidget != nullptr)
	{
		InteractionWidget->RemoveFromParent();
		bDelay = false;
	}

}

void AInteractableItem::TimelineFinished()
{
	bDoOnce = true;
}
