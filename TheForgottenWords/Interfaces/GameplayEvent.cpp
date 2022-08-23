// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/LevelStreaming.h"

#include "GameplayEvent.h"
#include "Kismet/GameplayStatics.h"


void IGameplayEvent::LoadSubLevel(const UObject* WorldContextObject, FName SubLevelName)
{
	if (SubLevelName != "None") UGameplayStatics::LoadStreamLevel(WorldContextObject, SubLevelName, true, true, LatentInfo);
}

void IGameplayEvent::UnloadSubLevel(const UObject* WorldContextObject, FName SubLevelName)
{
	if (SubLevelName != "None") UGameplayStatics::UnloadStreamLevel(WorldContextObject, SubLevelName, LatentInfo, false);
}

