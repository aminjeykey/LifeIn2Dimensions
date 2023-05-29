// Fill out your copyright notice in the Description page of Project Settings.


#include "LifeIn2Dimensions/UserInterface/MainHUD.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "LifeIn2Dimensions/UserInterface/InteractionWidget.h"

AMainHUD::AMainHUD()
{
	//
}

// Allowing widgets to be updated through hud
void AMainHUD::NotifyKeyCollected()
{
	KeysCollected++;
}

// Allowing widgets to be updated through hud
void AMainHUD::NotifyProjectileDestroyed()
{
	ProjectilesDestroyed++;
}

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PlayerController)
	{
		CrossHairWidget = CreateWidget(PlayerController, CrossHairWidgetTemplate);
		InteractionWidget = CreateWidget(PlayerController, InteractionWidgetTemplate);
		TodoWidget = CreateWidget(PlayerController, TodoWidgetTemplate);
	}
	if (CrossHairWidget)
	{
		AddWidgetToViewport(CrossHairWidget, 999);
	}
	if (InteractionWidget)
	{
		AddWidgetToViewport(InteractionWidget, 999);
	}
	if (TodoWidget)
	{
		AddWidgetToViewport(TodoWidget, 999);
	}
}

// Method for adding widget to player viewport (player 0 for standalone only)
void AMainHUD::AddWidgetToViewport(UUserWidget* Widget, const int32 ZOrder)
{
	Widget->AddToViewport();
}
