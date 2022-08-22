// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <TheForgottenWords/Player/PlayerCharacter.h>
#include <TheForgottenWords/Interfaces/GameplayEvent.h>
#include "Components/BoxComponent.h"

#include "BoxTriggerVolume.generated.h"

UENUM(BlueprintType)
enum EGameplayEventSelector
{

	GES_LoadSubLevel UMETA(DisplayName = "LoadSubLevel"),
	GES_MoveObject UMETA(DisplayName = "MoveObject")

};
UCLASS()
class THEFORGOTTENWORDS_API ABoxTriggerVolume : public AActor, public IGameplayEvent 
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoxTriggerVolume();

	UPROPERTY(EditAnywhere)
		TEnumAsByte<EGameplayEventSelector> Selector;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent*
			OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Collision")
		UBoxComponent* BoxCollision;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "SubLevel")
		FName SubLevelName;

};
