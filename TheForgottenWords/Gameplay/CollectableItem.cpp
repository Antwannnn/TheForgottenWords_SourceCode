// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectableItem.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACollectableItem::ACollectableItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(DefaultSceneRoot);

}

void ACollectableItem::PlayTakeSound()
{

	if (TakeSound != nullptr)
	{
		UGameplayStatics::PlaySound2D(this, TakeSound);
	}


}

void ACollectableItem::TimelineProgress(float Value)
{
	FadeIn = Value;
	const FVector NewLocation = FMath::Lerp(ObjectLoc, ViewLocation, FadeIn);
	const FRotator NewRotation = FMath::Lerp(ObjectRot, NewRot, FadeIn);
	SetActorLocationAndRotation(NewLocation, NewRotation);

}

void ACollectableItem::PlayInspectionAnimation(FVector Location)
{
	if (CurveFloat)
	{
		ViewLocation = Location;

		InterpFunction.BindUFunction(this, FName("TimelineProgress"));

		CurveTimeline.AddInterpFloat(CurveFloat, InterpFunction);
		CurveTimeline.SetPlayRate(PlayRate);

		ObjectLoc = GetActorLocation();
		ObjectRot = GetActorRotation();

		CurveTimeline.SetTimelineFinishedFunc(FinishedEvent);

		CurveTimeline.PlayFromStart();
	}

}

void ACollectableItem::TurnUp(float Value)
{
	const FRotator YawRotation(Value, 0.0f, 0.0f);
	const FRotator CombinedRotators = YawRotation + GetActorRotation();
	SetActorRotation(CombinedRotators);
}

void ACollectableItem::TurnLeft(float Value)
{
	const FRotator YawRotation(0.0f, (Value * -1.0f), 0.0f);
	const FRotator CombinedRotators = YawRotation + GetActorRotation();
	NewRot = CombinedRotators;
	SetActorRotation(CombinedRotators);
}




// Called when the game starts or when spawned
void ACollectableItem::BeginPlay()
{

	Super::BeginPlay();

}

// Called every frame
void ACollectableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurveTimeline.TickTimeline(DeltaTime);

}