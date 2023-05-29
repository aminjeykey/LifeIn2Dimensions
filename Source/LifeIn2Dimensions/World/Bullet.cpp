// Created by JKGames. codes written by Amin Jalali Karveh

#include "LifeIn2Dimensions/World/Bullet.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "LifeIn2Dimensions/World/EnemyProjectile.h"
#include "kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Instantiating default objects
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	BulletCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

	// Initializing sphere comp
	SetRootComponent(BulletCollider);
	BulletCollider->SetWorldScale3D(FVector(0.15f, 0.15f, 0.15f));
	BulletCollider->SetRelativeLocation(FVector::ZeroVector);

	// Initializing static mesh comp
	const ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshFinder(TEXT("/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule"));
	const ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialFinder(TEXT("/Game/Materials/M_EmissiveGold.M_EmissiveGold"));
	if (StaticMeshFinder.Succeeded())
	{
		BulletMesh->SetStaticMesh(StaticMeshFinder.Object);
	}
	if (MaterialFinder.Succeeded())
	{
		BulletMesh->SetMaterial(0, MaterialFinder.Object);
	}

	// Initializing particle effect
	const ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleFinder(TEXT("/Game/Realistic_Starter_VFX_Pack_Vol2/Particles/Destruction/P_Destruction_Building_A.P_Destruction_Building_A"));
	if (ParticleFinder.Succeeded())
	{
		DestructionEffect = ParticleFinder.Object;
	}

	// Setting up default values on components
	BulletMesh->SetupAttachment(RootComponent);
	BulletMesh->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	BulletMesh->SetSimulatePhysics(false);
	BulletMesh->SetEnableGravity(false);
	BulletMesh->SetRelativeLocation(FVector::ZeroVector);
	BulletMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BulletCollider->SetSimulatePhysics(true);
	BulletCollider->SetEnableGravity(false);
	BulletCollider->SetGenerateOverlapEvents(true);
	BulletCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BulletCollider->SetCollisionResponseToChannel(ECC_Visibility, ECR_Overlap);
	BulletCollider->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBulletHit);

	bGenerateOverlapEventsDuringLevelStreaming = false;
}

// On bullet hit event
void ABullet::OnBulletHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		AEnemyProjectile* Projectile = Cast<AEnemyProjectile>(OtherActor);
		if (Projectile)
		{
			Projectile->DestroyProjectile();
		}
	}
	if (DestructionEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestructionEffect, GetActorLocation());
	}
	Destroy();
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

