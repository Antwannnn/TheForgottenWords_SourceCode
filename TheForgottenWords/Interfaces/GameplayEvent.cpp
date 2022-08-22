// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayEvent.h"
#include "Kismet/GameplayStatics.h"

// Add default functionality here for any IGameplayEvent functions that are not pure virtual.
void IGameplayEvent::LoadSubLevel(const UObject* WorldContextObject, FName SubLevelName)
{

	if (SubLevelName != "")
	{
		const FLatentActionInfo LatentInfo;
		UGameplayStatics::LoadStreamLevel(WorldContextObject, SubLevelName, true, true, LatentInfo);
	}


}