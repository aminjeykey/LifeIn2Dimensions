// Created by JKGames. codes by Amin Jalali Karveh

#include "LifeIn2Dimensions/World/ExitDoor.h"
#include "LifeIn2Dimensions/LifeIn2DimensionsGameModeBase.h"
#include "kismet/GameplayStatics.h"
#include "kismet/KismetSystemLibrary.h"

// Overridden from parent (ATrigger) to trigger the exit door
void AExitDoor::DoInteraction()
{
	static ALifeIn2DimensionsGameModeBase* GameMode = Cast<ALifeIn2DimensionsGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (GameMode->bCanExit)
	{
		UKismetSystemLibrary::QuitGame(this, UGameplayStatics::GetPlayerController(this, 0), EQuitPreference::Quit, true);
	}
}
