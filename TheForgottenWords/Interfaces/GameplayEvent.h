// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayEvent.generated.h"

UENUM()
enum EGameplayEvent
{
	Ges_None UMETA(DisplayName = "None"),
	Ges_LoadSubLevel UMETA(DisplayName = "LoadSubLevel"),
	Ges_UnloadSubLevel UMETA(DisplayName = "UnloadSubLevel"),
	Ges_PlaySound2D UMETA(DisplayName = "PlaySound2D"),
	Ges_SpawnActor UMETA(DisplayName = "SpawnActor")

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
	virtual void LoadSubLevel(const UObject* WorldContextObject, FName SubLevelName);

	virtual void UnloadSubLevel(const UObject* WorldContextObject, FName SubLevelName);


protected:

	bool IsLevelLoaded(FName SubLevelName);

	FName tempLevelName;

	FLatentActionInfo LatentInfo;

};

