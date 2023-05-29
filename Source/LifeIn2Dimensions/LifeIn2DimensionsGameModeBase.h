// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LifeIn2DimensionsGameModeBase.generated.h"

class AMainHUD;

UCLASS()
class LIFEIN2DIMENSIONS_API ALifeIn2DimensionsGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	// Total keys to get for opening exit door
	UPROPERTY(EditDefaultsOnly, Category = "Exit Door")
	int16 TotalKeys = 12;

	// Current keys collected
	UPROPERTY(EditDefaultsOnly, Category = "Exit Door")
	int16 CurrentKeys = 0;

	// Total projectiles to destroy for spawning keys
	UPROPERTY(EditDefaultsOnly, Category = "Exit Door")
	int16 TotalProjectiles = 12;

	// Current projectiles destroyed
	UPROPERTY(EditDefaultsOnly, Category = "Exit Door")
	int16 CurrentProjectilesDestoyed = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Exit Door")
	bool bCanShowKeys = false;

	bool bCanExit = false;

	// Increase current keys value by 1
	UFUNCTION()
	void KeyCollected();

	// Increase projectiles destroyed value by 1
	UFUNCTION()
	void ProjectileDestroyed();

	// Opens exit door for player
	void OnAllKeysCollected();

	// Spawns all keys to be collected by player for opening exit door
	void OnAllProjectilesDestroyed();

protected:
	virtual void BeginPlay() override;

private:
	AMainHUD* GameMainHUD;

};
