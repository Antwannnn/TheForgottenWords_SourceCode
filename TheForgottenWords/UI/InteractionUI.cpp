// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractionUI.h"



void UInteractionUI::NativeConstruct()
{
	Super::NativeConstruct();

		
}

TSharedRef<SWidget> UInteractionUI::RebuildWidget()
{
	UPanelWidget* RootWidget = Cast<UPanelWidget>(GetRootWidget());

	if (!RootWidget)
	{
		RootWidget = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("RootWidget"));

		UCanvasPanelSlot* RootWidgetSlot = Cast<UCanvasPanelSlot>(RootWidget->Slot);

		if (RootWidgetSlot)
		{
			RootWidgetSlot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
			RootWidgetSlot->SetOffsets(FMargin(0.f, 0.f));
		}
		WidgetTree->RootWidget = RootWidget;
	}

	TSharedRef<SWidget> Widget = Super::RebuildWidget();

	if (RootWidget && WidgetTree)
	{

		Text = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("TextBase"));
		RootWidget->AddChild(Text);
		Text->SetText(TextContent);
		UCanvasPanelSlot* TextSlot = Cast<UCanvasPanelSlot>(Text->Slot);
		if (TextSlot)
		{
			TextSlot->SetAnchors(FAnchors(.5f, .5f, .5f, .5f));
			TextSlot->SetAlignment(FVector2D(.5f, -10.f));
			TextSlot->SetAutoSize(true);
		}


	}
	return Widget;
}

	

