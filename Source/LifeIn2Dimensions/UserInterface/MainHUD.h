// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

UCLASS()
class LIFEIN2DIMENSIONS_API AMainHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AMainHUD();

	// Allowing widgets to be updated through hud
	void NotifyKeyCollected();

	// Allowing widgets to be updated through hud
	void NotifyProjectileDestroyed();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Keys")
	int KeysCollected = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectiles")
	int ProjectilesDestroyed = 0;

protected:
	void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "User Widgets")
	TSubclassOf<UUserWidget> CrossHairWidgetTemplate;

	UPROPERTY(EditAnywhere, Category = "User Widgets")
	UUserWidget* CrossHairWidget;

	UPROPERTY(EditAnywhere, Category = "User Widgets")
	TSubclassOf<UUserWidget> TodoWidgetTemplate;

	UPROPERTY(EditAnywhere, Category = "User Widgets")
	UUserWidget* TodoWidget;

	UPROPERTY(EditAnywhere, Category = "User Widgets")
	TSubclassOf<UUserWidget> InteractionWidgetTemplate;

	UPROPERTY(EditAnywhere, Category = "User Widgets")
	UUserWidget* InteractionWidget;

private:
	// Method for adding widget to player viewport (player 0 for standalone only)
	void AddWidgetToViewport(UUserWidget* Widget, const int32 ZOrder);

};
