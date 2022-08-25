// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayEvent.h"
#include "Engine/LevelStreaming.h"
#include "Kismet/GameplayStatics.h"

//Level Loading / Unloading Section
void IGameplayEvent::LoadSubLevel(const UObject* WorldContextObject, FString SubLevelName)
{
	if (SubLevelName != "None")	UGameplayStatics::LoadStreamLevel(WorldContextObject, FName(SubLevelName), true, true, LatentInfo);

}

void IGameplayEvent::UnloadSubLevel(const UObject* WorldContextObject, FString SubLevelName)
{
	if (SubLevelName != "None") UGameplayStatics::UnloadStreamLevel(WorldContextObject, FName(SubLevelName), LatentInfo, true);
}

/*bool IGameplayEvent::IsLevelLoaded(FString SubLevelName)
{
	if (SubLevelName.Equals(tempLevelName))
		return true;
	else
		return false;
}
*/

//Linetrace Section
AActor* IGameplayEvent::LinetraceByChannel(float InTraceDistance, UWorld* World, AController* Controller)
{
	FVector Location;
	FRotator Rotation;
	FHitResult HitResult;

	Controller->GetPlayerViewPoint(Location, Rotation);

	FVector StartPoint = Location;
	FVector EndPoint = StartPoint + (Rotation.Vector() * InTraceDistance);

	FCollisionQueryParams TraceParams;

	bool bHit = World->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECC_Visibility, TraceParams);

		if (bHit)
			return HitResult.GetActor();
		else
			return nullptr;
}

AActor* IGameplayEvent::LinetraceByChannel(float InTraceDistance, UWorld* World, FVector Location, FRotator Rotation)
{
	FHitResult HitResult;

	FVector StartPoint = Location;
	FVector EndPoint = StartPoint + (Rotation.Vector() * InTraceDistance);

	FCollisionQueryParams TraceParams;

	bool bHit = World->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECC_Visibility, TraceParams);

	if (bHit)
		return HitResult.GetActor();
	else
		return nullptr;

}

void IGameplayEvent::ConstructWidget(TSubclassOf<UUserWidget> WidgetClass, UUserWidget* Widget, UWorld* World)
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





