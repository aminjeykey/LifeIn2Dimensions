// Created by JKGames. codes by Amin Jalali Karveh

#include "LifeIn2Dimensions/World/EnemyProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystem.h"
#include "LifeIn2Dimensions/LifeIn2DimensionsGameModeBase.h"

// Sets default values
AEnemyProjectile::AEnemyProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Creating components
	EmissiveMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EmissiveMesh"));
	EffectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EffectMesh"));

	// Feeding data from contents
	const ConstructorHelpers::FObjectFinder<USoundAttenuation> SoundAttenuationFinder(TEXT("/Game/NewSoundAttenuation.NewSoundAttenuation"));
	const ConstructorHelpers::FObjectFinder<USoundConcurrency> SoundConcurrencyFinder(TEXT("/Game/NewSoundConcurrency.NewSoundConcurrency"));
	if (SoundConcurrencyFinder.Succeeded() && SoundAttenuationFinder.Succeeded())
	{
		DestroyingSoundConcurrency = SoundConcurrencyFinder.Object;
		DestroyingSoundAttenuation = SoundAttenuationFinder.Object;
	}
	const ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystemFinder(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"));
	if (ParticleSystemFinder.Succeeded())
	{
		ExplosionEffect = ParticleSystemFinder.Object;
	}

	// Setting up default values for components
	EmissiveMesh->SetupAttachment(RootComponent);
	EffectMesh->SetupAttachment(EmissiveMesh);

	SetActorScale3D(FVector(0.5f, 0.5f, 0.5f));
	EmissiveMesh->SetGenerateOverlapEvents(true);
	EffectMesh->SetGenerateOverlapEvents(false);
}

// Destroy the actor
void AEnemyProjectile::DestroyProjectile()
{
	if (DestroyingSound && DestroyingSoundAttenuation && DestroyingSoundConcurrency)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DestroyingSound, GetActorLocation(), 1.0f, 1.0f, 0.0f, DestroyingSoundAttenuation, DestroyingSoundConcurrency);
		if (ExplosionEffect)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorTransform());
		}
	}
	static ALifeIn2DimensionsGameModeBase* MainGameMode = Cast<ALifeIn2DimensionsGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (MainGameMode)
	{
		MainGameMode->ProjectileDestroyed();
	}
	Destroy();
}

// Called when the game starts or when spawned
void AEnemyProjectile::BeginPlay()
{
	Super::BeginPlay();
}

