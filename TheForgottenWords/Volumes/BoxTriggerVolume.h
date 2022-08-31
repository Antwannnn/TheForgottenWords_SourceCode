// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundAttenuation.h"
#include <TheForgottenWords/Player/PlayerCharacter.h>
#include <TheForgottenWords/Libraries//GameplayEvents.h>
#include "Components/BoxComponent.h"

#include "BoxTriggerVolume.generated.h"


UCLASS()
class THEFORGOTTENWORDS_API ABoxTriggerVolume : public AActor 
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoxTriggerVolume();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void CallFunctionByEnumItem();

	UPROPERTY(EditAnywhere, Category = Functions)
		bool Repeat;

	UPROPERTY(EditAnywhere, Category = Functions)
		TEnumAsByte<EGameplayEvent> Selector;

	//

	//Level Loading an Unloading
	UPROPERTY(EditAnywhere, Category = Functions, meta = (EditCondition = "Selector == EGameplayEvent::GE_LoadSubLevel || Selector == EGameplayEvent::GE_UnloadSubLevel", EditConditionHides))
		FString SubLevelName;

	//Actor Spawning
	UPROPERTY(EditAnywhere, Category = Functions, meta = (EditCondition = "Selector == EGameplayEvent::GE_SpawnActor", EditConditionHides))
		TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditAnywhere, Category = Functions, meta = (EditCondition = "Selector == EGameplayEvent::GE_SpawnActor", EditConditionHides))
		FVector SpawnLocation;

	UPROPERTY(EditAnywhere, Category = Functions, meta = (EditCondition = "Selector == EGameplayEvent::GE_SpawnActor", EditConditionHides))
		FVector Scale;

	UPROPERTY(EditAnywhere, Category = Functions, meta = (EditCondition = "Selector == EGameplayEvent::GE_SpawnActor", EditConditionHides))
		FRotator SpawnRotation;

	//Actor moving
	UPROPERTY(EditAnywhere, Category = Functions, meta = (EditCondition = "Selector == EGameplayEvent::GE_SpawnActor", EditConditionHides))
		bool Hidden;

	UPROPERTY(EditAnywhere, Category = Functions, meta = (EditCondition = "Selector == EGameplayEvent::GE_MoveActor", EditConditionHides))
		AActor* ActorToMove;

	UPROPERTY(EditAnywhere, Category = Functions, meta = (EditCondition = "Selector == EGameplayEvent::GE_MoveActor", EditConditionHides))
		FTransform ObjectTransform;

	UPROPERTY(EditAnywhere, Category = Functions, meta = (EditCondition = "Selector == EGameplayEvent::GE_MoveActor", EditConditionHides))
		UCurveFloat* CurveFloat;

	UPROPERTY(EditAnywhere, Category = Functions, meta = (EditCondition = "Selector == EGameplayEvent::GE_MoveActor", EditConditionHides))
		float PlayRate;

	FTimeline Timeline;
	FOnTimelineFloat InterpFunction;

	FVector StartLoc;
	FVector EndLoc;

	FRotator StartRot;
	FRotator EndRot;

	UFUNCTION()
		void MoveActorTimeline();

	UFUNCTION()
		void TimelineProgress(float Value);

	//

	UPROPERTY(EditAnywhere, Category = Sound)
		USoundBase* TriggerSound;

	UPROPERTY(EditAnywhere, Category = Sound)
		USoundAttenuation* TriggerSoundAttenuation;

	UPROPERTY(EditAnywhere, Category = Sound, meta = (EditCondition = "TriggerSound != nullptr", EditConditionHides))
		FVector SoundLocation;

	UFUNCTION(CallInEditor)
		void OnBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent*
			OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Collision")
		UBoxComponent* BoxCollision;



public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:


};
