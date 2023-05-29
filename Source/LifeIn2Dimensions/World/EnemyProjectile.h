// Created by JKGames. codes by Amin Jalali Karveh

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyProjectile.generated.h"

class USoundBase;
class UParticleSystem;
class USoundAttenuation;
class USoundConcurrency;

UCLASS()
class LIFEIN2DIMENSIONS_API AEnemyProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyProjectile();

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UStaticMeshComponent* EmissiveMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UStaticMeshComponent* EffectMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* DestroyingSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundAttenuation* DestroyingSoundAttenuation;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundConcurrency* DestroyingSoundConcurrency;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* ExplosionEffect;

	// Destroy the actor
	void DestroyProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
