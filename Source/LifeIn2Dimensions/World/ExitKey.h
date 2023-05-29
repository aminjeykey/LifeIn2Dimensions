// Created by JKGames. codes by Amin Jalali Karveh

#pragma once

#include "CoreMinimal.h"
#include "LifeIn2Dimensions/World/Interactable.h"
#include "ExitKey.generated.h"

UCLASS()
class LIFEIN2DIMENSIONS_API AExitKey : public AInteractable
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AExitKey();

	// Overridden from parent (AInteractable) to destroy object and increase the keys collected in GameMode
	virtual void DoInteraction() override;
};
