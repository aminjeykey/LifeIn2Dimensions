// Created by JKGames. codes written by Amin Jalali Karveh

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionWidget.generated.h"

class UTextBlock;

UCLASS()
class LIFEIN2DIMENSIONS_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(EditAnywhere, Category = "User Widgets", meta = (BindWidget))
	UTextBlock* InteractionText;
	
};
