// Fill out your copyright notice in the Description page of Project Settings.


#include <TheForgottenWords/Libraries/GameplayEvents.h>
#include "DrawDebugHelpers.h"

//Level Loading / Unloading Section
void UGameplayEvents::LoadSubLevel(const UObject* WorldContextObject, FString SubLevelName, FLatentActionInfo LatentInfo)
{
	if (SubLevelName != "None")	UGameplayStatics::LoadStreamLevel(WorldContextObject, FName(SubLevelName), true, true, LatentInfo);

}

void UGameplayEvents::UnloadSubLevel(const UObject* WorldContextObject, FString SubLevelName, FLatentActionInfo LatentInfo)
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
AActor* UGameplayEvents::LinetraceByChannel(float InTraceDistance, UWorld* World, AController* Controller)
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

AActor* UGameplayEvents::LinetraceByChannel(float InTraceDistance, UWorld* World, FVector Location, FRotator Rotation)
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