// Fill out your copyright notice in the Description page of Project Settings.

#include "LifeIn2Dimensions/World/Trigger.h"

ATrigger::ATrigger()
{
	Tags.Add("Triggerable");
}

// Triggers the triggerable
void ATrigger::DoInteraction()
{
	GEngine->AddOnScreenDebugMessage(-3, 1.0f, FColor::Cyan, "Object Triggered!");
}
