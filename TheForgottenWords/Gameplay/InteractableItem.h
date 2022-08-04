// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableItem.generated.h"

UCLASS()
class THEFORGOTTENWORDS_API AInteractableItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableItem();
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Rendering)
		UStaticMeshComponent* Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FText Text;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
