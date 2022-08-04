// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/StaticMeshComponent.h"
#include "CollectableItem.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACollectableItem::ACollectableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

}

void ACollectableItem::PlayTakeSound(USoundBase* Sound)
{
	if (Sound != nullptr)
	{
		UGameplayStatics::PlaySound2D(this, Sound);
	}
	

}

// Called when the game starts or when spawned
void ACollectableItem::BeginPlay()
{
	Super::BeginPlay();

	PlayTakeSound(TakeSound);
	
}

// Called every frame
void ACollectableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

