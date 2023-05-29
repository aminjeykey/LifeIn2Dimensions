// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LifeIn2Dimensions/World/Interactable.h"
#include "Trigger.generated.h"

UCLASS()
class LIFEIN2DIMENSIONS_API ATrigger : public AInteractable
{
	GENERATED_BODY()
	
protected:
	ATrigger();

	// Triggers the triggerable
	virtual void DoInteraction() override;

};
