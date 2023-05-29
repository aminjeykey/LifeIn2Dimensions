// Created by JKGames. codes by Amin Jalali Karveh

#include "LifeIn2Dimensions/World/ExitKey.h"
#include "kismet/GameplayStatics.h"
#include "LifeIn2Dimensions/LifeIn2DimensionsGameModeBase.h"

// Sets default values for this actor's properties
AExitKey::AExitKey()
{
	const ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshFinder(TEXT("/Game/SM_Key.SM_Key"));
	const ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialFinder(TEXT("/Game/Materials/M_EmissiveGold.M_EmissiveGold"));
	if (StaticMeshFinder.Succeeded())
	{
		StaticMeshComponent->SetStaticMesh(StaticMeshFinder.Object);
	}
	StaticMeshComponent->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
	if (MaterialFinder.Succeeded())
	{
		StaticMeshComponent->SetMaterial(0, MaterialFinder.Object);
	}
	StaticMeshComponent->SetSimulatePhysics(false);
}

// Overridden from parent (AInteractable) to destroy object and increase the keys collected in GameMode
void AExitKey::DoInteraction()
{
	static ALifeIn2DimensionsGameModeBase* MainGameMode = Cast<ALifeIn2DimensionsGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (MainGameMode)
	{
		MainGameMode->KeyCollected();
	}
	Destroy();
}
