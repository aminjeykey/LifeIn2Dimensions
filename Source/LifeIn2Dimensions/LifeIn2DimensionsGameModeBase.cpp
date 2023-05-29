// Copyright Epic Games, Inc. All Rights Reserved.

#include "LifeIn2DimensionsGameModeBase.h"
#include "LifeIn2Dimensions/UserInterface/MainHUD.h"
#include "kismet/GameplayStatics.h"

// Increase current keys value by 1
void ALifeIn2DimensionsGameModeBase::KeyCollected()
{
	CurrentKeys++;
	if (CurrentKeys >= TotalKeys)
	{
		OnAllKeysCollected();
	}
}

// Increase projectiles destroyed value by 1
void ALifeIn2DimensionsGameModeBase::ProjectileDestroyed()
{
	CurrentProjectilesDestoyed++;
	if (CurrentProjectilesDestoyed >= TotalProjectiles)
	{
		OnAllProjectilesDestroyed();
	}
}

// Opens exit door for player
void ALifeIn2DimensionsGameModeBase::OnAllKeysCollected()
{
	//GEngine->AddOnScreenDebugMessage(-19, 2.0f, FColor::Blue, TEXT("All Keys Collected!"));
	bCanExit = true;
}

// Spawns all keys to be collected by player for opening exit door
void ALifeIn2DimensionsGameModeBase::OnAllProjectilesDestroyed()
{
	//GEngine->AddOnScreenDebugMessage(-19, 2.0f, FColor::Blue, TEXT("All Projectiles Destroyed!"));
	bCanShowKeys = true;
}

void ALifeIn2DimensionsGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	const AController* Controller = UGameplayStatics::GetPlayerPawn(this, 0)->GetController();
	if (Controller)
	{
		AMainHUD* HUD = Cast<AMainHUD>(Cast<APlayerController>(Controller)->GetHUD());
		if (HUD)
		{
			GameMainHUD = HUD;
		}
	}
}
