// Fill out your copyright notice in the Description page of Project Settings.


#include "LifeIn2Dimensions/Player/ThirdPersonCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "LifeIn2Dimensions/World/Interactable.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "LifeIn2Dimensions/Player/Gun.h"
#include "Engine/PostProcessVolume.h"
#include "LifeIn2Dimensions/World/ObjectEmitter.h"

// Sets default values
AThirdPersonCharacter::AThirdPersonCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creating Sub Objects of components
	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	PhysicsHandleComponent = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandleComponent"));
	GrabbedObjectScenComponent = CreateDefaultSubobject<USceneComponent>(TEXT("GrabbedObjScenComponent"));
	GunLocation = CreateDefaultSubobject<USceneComponent>(TEXT("GunLocationScenComponent"));

	// Initializing skeletal mesh component
	const ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshFinder(TEXT("/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin"));
	if (SkeletalMeshFinder.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SkeletalMeshFinder.Object);
	}

	// Initializing spring arm component
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->TargetArmLength = 200.0f;
	SpringArmComponent->bInheritPitch = true;
	SpringArmComponent->bInheritYaw = true;
	SpringArmComponent->bInheritRoll = false;
	
	// Initializing camera component
	ThirdPersonCamera->SetupAttachment(SpringArmComponent);
	ThirdPersonCamera->SetFieldOfView(120.0f);

	// Initializing character component
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	// Initializing physics handle component
	PhysicsHandleComponent->bSoftAngularConstraint = true;
	PhysicsHandleComponent->bSoftLinearConstraint = true;
	PhysicsHandleComponent->LinearDamping = 300.0f;
	PhysicsHandleComponent->LinearStiffness = 750.0f;

	// Initializing scene component
	GrabbedObjectScenComponent->SetupAttachment(GetMesh());

	// Initializing gun location component
	GunLocation->SetupAttachment(GetMesh());
}

// Called when the game starts or when spawned
void AThirdPersonCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Get AMainHUD from player controller
	/*if (Controller)
	{
		HUD = Cast<AMainHUD>(Cast<APlayerController>(Controller)->GetHUD());
	}
	if (HUD)
	{

	}*/

	// Setting up gun location and attachments
	const FAttachmentTransformRules AttatchmentTransformRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true);
	Gun->SetActorLocation(FVector::ZeroVector);
	if (GetMesh()->DoesSocketExist("GunSocket"))
	{
		Gun->AttachToComponent(GetMesh(), AttatchmentTransformRules, TEXT("GunSocket"));
	}

	//if (TeleportationEffect)
	//{
	//	// This spawns the chosen effect on the owning WeaponMuzzle SceneComponent
	//	TeleportationComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(TeleportationEffect, GetActorLocation(), NAME_None, FVector(0.f), FRotator(0.f), EAttachLocation::Type::KeepRelativeOffset, true);
	//}
}

// Method for finding and applying input in X direction
void AThirdPersonCharacter::MoveForward(float Axis)
{
	FVector Direction = GetActorForwardVector();
	AddMovementInput(Direction, Axis);
}

// Method for finding and applying input in Y direction
void AThirdPersonCharacter::MoveRight(float Axis)
{
	FVector Direction = GetActorRightVector();
	AddMovementInput(Direction, Axis);
}

// Mouse Rotation on X axis
void AThirdPersonCharacter::MouseYaw(float Axis)
{
	AddControllerYawInput(Axis * MouseXSensitivity * FApp::GetDeltaTime());
}

// Mouse Rotation on Y axis
void AThirdPersonCharacter::MousePitch(float Axis)
{
	AddControllerPitchInput(Axis * MouseYSensitivity * FApp::GetDeltaTime());
}

// On Interact hit event
void AThirdPersonCharacter::OnInteractPressed()
{
	if (CurrentInteractable)
	{
		TArray<FName> ObjTags;
		ObjTags = CurrentInteractable->Tags;
		for (int i = 0; i < ObjTags.Num(); i++)
		{
			if (ObjTags[i].Compare("Grabbable") == 0)
			{
				PhysicsHandleComponent->GrabComponentAtLocationWithRotation(CurrentInteractable->FindComponentByClass<UPrimitiveComponent>(), "", CurrentInteractable->GetActorLocation(), CurrentInteractable->GetActorRotation());
				bIsGrabbingObject = true;
				bCanShoot = false;
				return;
			}
			else if (ObjTags[i].Compare("Triggerable") == 0)
			{
				CurrentInteractable->DoInteraction();
			}
			else if (ObjTags[i].Compare("Key") == 0)
			{
				CurrentInteractable->DoInteraction();
			}
		}
	}
}

// On Interact released event
void AThirdPersonCharacter::OnInteractReleased()
{
	if (bIsGrabbingObject)
	{
		PhysicsHandleComponent->ReleaseComponent();
		bIsGrabbingObject = false;
		bCanShoot = true;
	}
}

// Start shooting a bullet
void AThirdPersonCharacter::StartShooting()
{
	if (Gun && bCanShoot)
	{
		Gun->Shoot(GetBaseAimRotation().Vector());
		bCanShoot = false;
	}
}

// Stop shooting bullets
void AThirdPersonCharacter::EndShooting()
{
	bCanShoot = true;
}

// Shift to the other dimension (Setting up post processing effects and objects to be visible in a dimension)
void AThirdPersonCharacter::ShiftDimension()
{
	if (GreenWorldPostProcessVolume && RedWorldPostProcessVolume)
	{
		if (GreenWorldPostProcessVolume->bEnabled && !RedWorldPostProcessVolume->bEnabled)
		{
			GreenWorldPostProcessVolume->bEnabled = false;
			RedWorldPostProcessVolume->bEnabled = true;
			if (ObjectEmitterComponent)
			{
				ObjectEmitterComponent->SetKeysHiddenInGame(true);
				ObjectEmitterComponent->SetProjectilesHiddenInGame(false);
			}
		}
		else
		{
			GreenWorldPostProcessVolume->bEnabled = true;
			RedWorldPostProcessVolume->bEnabled = false;
			if (ObjectEmitterComponent)
			{
				ObjectEmitterComponent->SetKeysHiddenInGame(false);
				ObjectEmitterComponent->SetProjectilesHiddenInGame(true);
			}
		}
	}
}

void AThirdPersonCharacter::EndShiftDimension()
{
	//
}

// Called every frame
void AThirdPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Linetracing to find interactables and letting widget blueprints to show text
	const FVector StartPoint = ThirdPersonCamera->GetComponentLocation();
	const FVector EndPoint = StartPoint + ThirdPersonCamera->GetForwardVector() * 400.0f;
	AInteractable* InteractableObj = FindInteractable(GetWorld(), StartPoint, EndPoint);
	if (!bIsGrabbingObject)
	{
		if (InteractableObj)
		{
			CurrentInteractable = InteractableObj;
			ShouldShowInteractionUI(true);
			bCanInteract = true;
		}
		else
		{
			CurrentInteractable = nullptr;
			ShouldShowInteractionUI(false);
			bCanInteract = false;
		}
	}
	else
	{
		PhysicsHandleComponent->SetTargetLocation(EndPoint);
		bCanInteract = false;
	}
}

// Called to bind functionality to input
void AThirdPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Binding Axis
	PlayerInputComponent->BindAxis("MoveForward", this, &AThirdPersonCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AThirdPersonCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MouseYaw", this, &AThirdPersonCharacter::MouseYaw);
	PlayerInputComponent->BindAxis("MousePitch", this, &AThirdPersonCharacter::MousePitch);

	// Binding Actions
	PlayerInputComponent->BindAction("Interact", EInputEvent::IE_Pressed, this, &AThirdPersonCharacter::OnInteractPressed);
	PlayerInputComponent->BindAction("Interact", EInputEvent::IE_Released, this, &AThirdPersonCharacter::OnInteractReleased);
	PlayerInputComponent->BindAction("Shoot", EInputEvent::IE_Pressed, this, &AThirdPersonCharacter::StartShooting);
	PlayerInputComponent->BindAction("Shoot", EInputEvent::IE_Released, this, &AThirdPersonCharacter::EndShooting);
	PlayerInputComponent->BindAction("ShiftDimension", EInputEvent::IE_Released, this, &AThirdPersonCharacter::ShiftDimension);
	PlayerInputComponent->BindAction("ShiftDimension", EInputEvent::IE_Released, this, &AThirdPersonCharacter::EndShiftDimension);
}

// Method for finding intractable actors
AInteractable* AThirdPersonCharacter::FindInteractable(UWorld* WorldInstace, const FVector& StartPoint, const FVector& EndPoint)
{
	FHitResult HitResult;
	bool bDidHit = WorldInstace->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECollisionChannel::ECC_Visibility);
	if (bDidHit)
	{
		AInteractable* InteractableObj = Cast<AInteractable>(HitResult.Actor);
		if (InteractableObj)
		{
			return InteractableObj;
		}
	}
	return nullptr;
}

// Method for notifying HUD to update widgets
void AThirdPersonCharacter::ShouldShowInteractionUI(bool Flag) const
{
	//
}

