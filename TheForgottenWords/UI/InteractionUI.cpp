// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/World.h"
#include "InteractionUI.h"

void UInteractionUI::NativeConstruct()
{
	Super::NativeConstruct();
	GetWorld()->GetTimerManager().SetTimer(TH_WidgetDelayManager, this, &UInteractionUI::Delay, 3, false);
}

void UInteractionUI::Delay()
{

	RemoveFromParent();

}

	

