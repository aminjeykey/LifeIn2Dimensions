// Created by JKGames. codes written by Amin Jalali Karveh


#include "LifeIn2Dimensions/Player/Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "LifeIn2Dimensions/World/Bullet.h"
#include "kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Instantiating default objects
	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	MuzzleSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzelScenComponent"));

	// Initializing Gun component
	GunMesh->SetupAttachment(RootComponent);
	const ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshFinder(TEXT("/Game/FPS_Weapon_Bundle/Weapons/Meshes/AR4/SK_AR4_X.SK_AR4_X"));
	if (SkeletalMeshFinder.Succeeded())
	{
		GunMesh->SetSkeletalMesh(SkeletalMeshFinder.Object);
	}
	// Feeding gun sound from contents
	const ConstructorHelpers::FObjectFinder<USoundBase> SoundFinder(TEXT("/Game/SoundEffects/single-gunshot-62-hp-37188.single-gunshot-62-hp-37188"));
	if (SoundFinder.Succeeded())
	{
		GunShotSound = SoundFinder.Object;
	}
	// Feeding muzzle effect from contents
	const ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleFinder(TEXT("/Game/Realistic_Starter_VFX_Pack_Vol2/Particles/Hit/P_Default.P_Default"));
	if (ParticleFinder.Succeeded())
	{
		ShootingEffect = ParticleFinder.Object;
	}

	// Initializing Muzzle scene component
	MuzzleSceneComponent->SetupAttachment(GunMesh);
	MuzzleSceneComponent->SetWorldLocation(FVector(60.0f, 0.0f, 10.0f));
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
	WorldInstance = GetWorld();
}

// Method to be called by player for shooting in specified direction
void AGun::Shoot(const FVector Direction)
{
	if (WorldInstance)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		const ABullet* Bullet = WorldInstance->SpawnActor<ABullet>(MuzzleSceneComponent->GetComponentLocation(), FRotator(), SpawnParams);
		AddBulletForce(Bullet, Direction);
		if (GunShotSound)
		{
			UGameplayStatics::PlaySound2D(this, GunShotSound);
		}
		if (ShootingEffect)
		{
			UGameplayStatics::SpawnEmitterAttached(ShootingEffect, MuzzleSceneComponent);
		}
	}
}

// Method for adding force to bullets that spawn by Shoot() method
void AGun::AddBulletForce(const ABullet* Bullet, const FVector Direction) const
{
	if (!Bullet)
	{
		return;
	}
	USphereComponent* BulletSphereComp = Bullet->FindComponentByClass<USphereComponent>();
	if (BulletSphereComp)
	{
		BulletSphereComp->AddImpulse(Direction * BulletSpeed);
	}
}

