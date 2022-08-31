// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "GameplayEvents.generated.h"

/**
 * 
 */

UENUM()
enum EGameplayEvent
{
	GE_None UMETA(DisplayName = "None"),
	GE_LoadSubLevel UMETA(DisplayName = "LoadSubLevel"),
	GE_UnloadSubLevel UMETA(DisplayName = "UnloadSubLevel"),
	GE_SpawnActor UMETA(DisplayName = "SpawnActor"),
	GE_MoveActor UMETA(DisplayName = "MoveActor"),

};

UCLASS()
class THEFORGOTTENWORDS_API UGameplayEvents : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()



public:

	//Every necessary methods to perform in-game actions.
	//Level loading related methods
	UFUNCTION(BlueprintCallable)
		static void LoadSubLevel(const UObject* WorldContextObject, FString SubLevelName, FLatentActionInfo LatentInfo);
	UFUNCTION(BlueprintCallable)
		static void UnloadSubLevel(const UObject* WorldContextObject, FString SubLevelName, FLatentActionInfo LatentInfo);

	//Linetrace related methods
	//LinetraceByChannel method overloading
	UFUNCTION(BlueprintCallable)
		static AActor* LinetraceByChannel(float InTraceDistance, UWorld* World, AController* Controller);
		static AActor* LinetraceByChannel(float InTraceDistance, UWorld* World, FVector Location, FRotator Rotation);

	//Actor behaviour related methods
	//Spawn actor method overloading
	UFUNCTION(BlueprintCallable)
	static void SpawnActor(TSubclassOf<AActor> InActor, UWorld* World, FVector InLoc, FRotator InRot, FVector InScale3D);
	static void SpawnActor(TSubclassOf<AActor> InActor, UWorld* World, FVector InLoc, FRotator InRot, FVector InScale3D, FActorSpawnParameters SpawnParams);

protected:


private:

	//Level loading
	//bool IsLevelLoaded(FString SubLevelName);
	static FString tempLevelName;

};
