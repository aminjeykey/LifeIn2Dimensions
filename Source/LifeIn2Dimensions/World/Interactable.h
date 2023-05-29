// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

class UStaticMeshComponent;

UCLASS()
class LIFEIN2DIMENSIONS_API AInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable();

	UPROPERTY(EditAnywhere, Category = "Static Mesh")
	UStaticMeshComponent* StaticMeshComponent;

public:
	// Interaction method to be executed and is inherited by 
	virtual void DoInteraction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
