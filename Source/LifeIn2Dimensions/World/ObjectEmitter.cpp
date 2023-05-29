// Created by JKGames. codes by Amin Jalali Karveh

#include "LifeIn2Dimensions/World/ObjectEmitter.h"
#include "LifeIn2Dimensions/World/ExitKey.h"
#include "LifeIn2Dimensions/World/EnemyProjectile.h"
#include "kismet/GameplayStatics.h"
#include "LifeIn2Dimensions/LifeIn2DimensionsGameModeBase.h"

// Sets default values
AObjectEmitter::AObjectEmitter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Set all keys to be visible in game
void AObjectEmitter::SetKeysHiddenInGame(bool bIsHidden) const
{
	if (!bIsHidden)
	{
		static ALifeIn2DimensionsGameModeBase* GameMode = Cast<ALifeIn2DimensionsGameModeBase>(UGameplayStatics::GetGameMode(this));
		if (!GameMode->bCanShowKeys)
		{
			return;
		}
	}
	for (int i = 0; i < ExitKeys.Num(); i++)
	{
		if (ExitKeys[i])
		{
			ExitKeys[i]->SetActorHiddenInGame(bIsHidden);
		}
	}
}

// Set all projectiles to be visible in game
void AObjectEmitter::SetProjectilesHiddenInGame(bool bIsHidden) const
{
	for (int i = 0; i < Projectiles.Num(); i++)
	{
		if (Projectiles[i])
		{
			Projectiles[i]->SetActorHiddenInGame(bIsHidden);
		}
	}
}

// Called when the game starts or when spawned
void AObjectEmitter::BeginPlay()
{
	Super::BeginPlay();
	
	InitArrays();
}

// Initialize arrays
void AObjectEmitter::InitArrays() const
{
	SetKeysHiddenInGame(true);
	SetProjectilesHiddenInGame(true);
}
