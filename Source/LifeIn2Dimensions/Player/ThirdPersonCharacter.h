// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ThirdPersonCharacter.generated.h"

class AGun;
class AMainHUD;
class AInteractable;
class AObjectEmitter;
class UCameraComponent;
class APostProcessVolume;
class USpringArmComponent;
class UPhysicsHandleComponent;

UCLASS()
class LIFEIN2DIMENSIONS_API AThirdPersonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AThirdPersonCharacter();

protected:
	// Mouse X axis Sensitivity
	UPROPERTY(EditAnywhere, Category = "Mouse")
	float MouseXSensitivity = 100.0f;

	// Mouse Y axis Sensitivity
	UPROPERTY(EditAnywhere, Category = "Mouse")
	float MouseYSensitivity = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThirdPersonCamera")
	UCameraComponent* ThirdPersonCamera;

	UPROPERTY(EditAnywhere, Category = "ThirdPersonCamera")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
	AGun* Gun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
	USceneComponent* GunLocation;

	UPROPERTY(EditAnywhere, Category = "Physics")
	UPhysicsHandleComponent* PhysicsHandleComponent;

	UPROPERTY(EditAnywhere, Category = "Physics")
	USceneComponent* GrabbedObjectScenComponent;

	/*UPROPERTY(EditAnywhere, Category = "HUD")
	AMainHUD* HUD;*/

	UPROPERTY(EditAnywhere, Category = "Other Dimension")
	APostProcessVolume* GreenWorldPostProcessVolume;

	UPROPERTY(EditAnywhere, Category = "Other Dimension")
	APostProcessVolume* RedWorldPostProcessVolume;

	UPROPERTY(EditAnywhere, Category = "Other Dimension")
	AObjectEmitter* ObjectEmitterComponent;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Method for finding and applying input in X direction
	void MoveForward(float Axis);

	// Method for finding and applying input in Y direction
	void MoveRight(float Axis);

	// Mouse Rotation on X axis
	void MouseYaw(float Axis);

	// Mouse Rotation on Y axis
	void MousePitch(float Axis);

	// On Interact hit event
	void OnInteractPressed();

	// On Interact Release event
	void OnInteractReleased();

	// Start shooting a bullet
	void StartShooting();

	// Stop shooting bullets
	void EndShooting();

	// Shift to the other dimension (Setting up post processing effects and objects to be visible in a dimension)
	UFUNCTION(BlueprintCallable)
	void ShiftDimension();

	void EndShiftDimension();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Can player interact or not
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bCanInteract = false;

private:
	// Method for finding intractable actors
	AInteractable* FindInteractable(UWorld* WorldInstace, const FVector& StartPoint, const FVector& EndPoint);

	// Method for notifying HUD to update widgets
	void ShouldShowInteractionUI(bool Flag) const;

	// the current interactable object
	AInteractable* CurrentInteractable;

	// Boolean to update picked up object every frame if set to true
	bool bIsGrabbingObject = false;

	// Boolean for stoping the player to spam shooting bullets
	bool bCanShoot = true;
};
