// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxTriggerVolume.h"
#include "Kismet/GameplayStatics.h"
#include <Engine/LevelStreaming.h>

#define stringify( name ) #name

// Sets default values
ABoxTriggerVolume::ABoxTriggerVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));

	RootComponent = BoxCollision;

}

void ABoxTriggerVolume::OnBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if(Cast<APlayerCharacter>(OtherActor))
	{
		CallFunctionByEnumItem();
		K2_DestroyActor();
	}


}



// Called when the game starts or when spawned
void ABoxTriggerVolume::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ABoxTriggerVolume::OnBeginOverlap);
	
}

void ABoxTriggerVolume::CallFunctionByEnumItem()
{
	switch (Selector)
	{
	case Ges_LoadSubLevel:  return IGameplayEvent::LoadSubLevel(this, SubLevelName);
	case Ges_UnloadSubLevel:  return IGameplayEvent::UnloadSubLevel(this, SubLevelName);
	}
}

// Called every frame
void ABoxTriggerVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



