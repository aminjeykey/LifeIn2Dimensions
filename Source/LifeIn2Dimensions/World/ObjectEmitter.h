// Created by JKGames. codes by Amin Jalali Karveh

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectEmitter.generated.h"

class AExitKey;
class AEnemyProjectile;

UCLASS()
class LIFEIN2DIMENSIONS_API AObjectEmitter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectEmitter();

	// Set all keys to be visible in game
	void SetKeysHiddenInGame(bool bIsHidden) const;

	// Set all projectiles to be visible in game
	void SetProjectilesHiddenInGame(bool bIsHidden) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// The array of existing keys
	UPROPERTY(EditAnywhere, Category = "Emitter Array")
	TArray<AExitKey*> ExitKeys;

	// The array of existing projectiles
	UPROPERTY(EditAnywhere, Category = "Emitter Array")
	TArray<AEnemyProjectile*> Projectiles;

private:
	// Initialize arrays
	void InitArrays() const;

};
