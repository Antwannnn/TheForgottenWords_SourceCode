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
		if(!Repeat)
		{
			K2_DestroyActor();
		}
		const FVector FinalLocation = SoundLocation + UGameplayStatics::GetPlayerCharacter(this, 0)->GetActorLocation();
		UGameplayStatics::PlaySoundAtLocation(this, TriggerSound, FinalLocation, 1, 1, 0, TriggerSoundAttenuation);

	}


}
void ABoxTriggerVolume::CallFunctionByEnumItem()
{
	switch (Selector)
	{
	case GE_LoadSubLevel:  return UGameplayEvents::LoadSubLevel(this, SubLevelName, FLatentActionInfo());
	case GE_UnloadSubLevel:  return UGameplayEvents::UnloadSubLevel(this, SubLevelName, FLatentActionInfo());
	}
}


// Called when the game starts or when spawned
void ABoxTriggerVolume::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ABoxTriggerVolume::OnBeginOverlap);
	
}

// Called every frame
void ABoxTriggerVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



