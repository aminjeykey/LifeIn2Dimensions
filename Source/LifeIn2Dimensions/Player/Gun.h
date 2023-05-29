// Created by JKGames. codes written by Amin Jalali Karveh

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

class USkeletalMeshComponent;
class UParticleSystem;
class USoundBase;
class ABullet;

UCLASS()
class LIFEIN2DIMENSIONS_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Skeletal Mesh Component")
	USkeletalMeshComponent* GunMesh;

	UPROPERTY(EditAnywhere, Category = "Muzzle")
	USceneComponent* MuzzleSceneComponent;

	UPROPERTY(EditAnywhere, Category = "Bullet")
	TSubclassOf<ABullet> BulletType;

	UPROPERTY(EditAnywhere, Category = "Bullet")
	float BulletSpeed = 2000.0f;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* GunShotSound;

	UPROPERTY(EditAnywhere, Category = "Effect")
	UParticleSystem* ShootingEffect;

public:	
	// Method to be called by player for shooting in specified direction
	void Shoot(const FVector Direction);


private:
	// Current world instance for using multiple times
	UWorld* WorldInstance;

	// Method for adding force to bullets that spawn by Shoot() method
	void AddBulletForce(const ABullet* Bullet, const FVector Direction) const;

};
