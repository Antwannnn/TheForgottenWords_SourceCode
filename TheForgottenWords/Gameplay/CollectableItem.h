// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Components/SceneComponent.h"


#include "CollectableItem.generated.h"

UCLASS()
class THEFORGOTTENWORDS_API ACollectableItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectableItem();

	//All the uproperty that I will be using for the collectible item.
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FText Title;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FText Description;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool bTakeable = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		USoundBase* TakeSound;

	UFUNCTION(BlueprintCallable)
		void PlayTakeSound();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Rendering)
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USceneComponent* DefaultSceneRoot;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
