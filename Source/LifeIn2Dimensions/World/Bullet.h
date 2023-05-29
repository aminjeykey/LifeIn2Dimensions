// Created by JKGames. codes written by Amin Jalali Karveh

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

class UParticleSystem;
class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class LIFEIN2DIMENSIONS_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	UPROPERTY(EditAnywhere, Category = "Static Mesh")
	UStaticMeshComponent* BulletMesh;

	UPROPERTY(EditAnywhere, Category = "Collision")
	USphereComponent* BulletCollider;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* DestructionEffect;

	// On bullet hit event
	UFUNCTION()
	void OnBulletHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
