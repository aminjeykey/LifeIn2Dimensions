// Created by JKGames. codes by Amin Jalali Karveh

#pragma once

#include "CoreMinimal.h"
#include "LifeIn2Dimensions/World/Trigger.h"
#include "ExitDoor.generated.h"

UCLASS()
class LIFEIN2DIMENSIONS_API AExitDoor : public ATrigger
{
	GENERATED_BODY()
	
public:
	// Overridden from parent (ATrigger) to trigger the exit door
	virtual void DoInteraction() override;

};
