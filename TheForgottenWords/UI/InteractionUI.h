// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionUI.generated.h"

UCLASS()
class THEFORGOTTENWORDS_API UInteractionUI : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite)
		FText TextContent = FText::FromString(TEXT("Default"));

protected:
		
	virtual void NativeConstruct() override;
};
