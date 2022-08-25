// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "UObject/Interface.h"
#include "GameplayEvent.generated.h"

UENUM()
enum EGameplayEvent
{
	GE_None UMETA(DisplayName = "None"),
	GE_LoadSubLevel UMETA(DisplayName = "LoadSubLevel"),
	GE_UnloadSubLevel UMETA(DisplayName = "UnloadSubLevel"),

};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGameplayEvent : public UInterface
{
	GENERATED_BODY()
};


class THEFORGOTTENWORDS_API IGameplayEvent
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.

public:

	//Every Method needed to perform in-game actions.
	void LoadSubLevel(const UObject* WorldContextObject, FString SubLevelName);

	void UnloadSubLevel(const UObject* WorldContextObject, FString SubLevelName);

	//LinetraceByChannel method overloading
	AActor* LinetraceByChannel(float InTraceDistance, UWorld* World, AController* Controller);
	AActor* LinetraceByChannel(float InTraceDistance, UWorld* World, FVector Location, FRotator Rotation);




protected:

	//Level loading
	//bool IsLevelLoaded(FString SubLevelName);
	FString tempLevelName;
	FLatentActionInfo LatentInfo;


};

