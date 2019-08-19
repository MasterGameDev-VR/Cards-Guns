// Cards&Guns 2019

#include "CardsAndGunsCharacter.h"
#include "CardsAndGunsProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "HealerBot.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// ACardsAndGunsCharacter

ACardsAndGunsCharacter::ACardsAndGunsCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

// 	//Create a gun mesh component
// 	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
// 	FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
// 	FP_Gun->bCastDynamicShadow = false;
// 	FP_Gun->CastShadow = false;
// 	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
// 	FP_Gun->SetupAttachment(RootComponent);
// 
// 	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
// 	FP_MuzzleLocation->SetupAttachment(FP_Gun);
// 	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P and FP_Gun
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.
}

void ACardsAndGunsCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	//FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	
	if (WeaponClass == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Weapon class not found."));
		return;
	}

	Weapon = GetWorld()->SpawnActor<AHitscanWeapon>(WeaponClass);
	
	if (Weapon != nullptr)
	{
		Weapon->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	}

	// Show or hide the gun
	Mesh1P->SetHiddenInGame(false, true);
}

//////////////////////////////////////////////////////////////////////////
// Input

void ACardsAndGunsCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ACardsAndGunsCharacter::OnFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ACardsAndGunsCharacter::StopFire);

	// Bind Reload event
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ACardsAndGunsCharacter::ReloadWeapon);

	// Bind switchautomatic event
	PlayerInputComponent->BindAction("SwitchAutomatic", IE_Pressed, this, &ACardsAndGunsCharacter::SwitchFireType);

	// Bind SpawnHealerBot event
	PlayerInputComponent->BindAction("SpawnHealerBot", IE_Pressed, this, &ACardsAndGunsCharacter::SpawnHealerBot);
	
	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ACardsAndGunsCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACardsAndGunsCharacter::MoveRight);


	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ACardsAndGunsCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ACardsAndGunsCharacter::LookUpAtRate);

}

void ACardsAndGunsCharacter::OnFire()
{
	Weapon->AnimInstance1P = Mesh1P->GetAnimInstance();
	Weapon->OnFire();
}

void ACardsAndGunsCharacter::StopFire()
{
	if (Weapon->IsAutomaticFire)
	{
		Weapon->StopFire();
	}

}

void ACardsAndGunsCharacter::ReloadWeapon()
{
	Weapon->Reload();
}



void ACardsAndGunsCharacter::SwitchFireType()
{
	Weapon->SwitchAutomatic();
}

void ACardsAndGunsCharacter::SpawnHealerBot()
{
	//TODO Forse � meglio spostarle nel beginplay? 
	if (HealerClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Healer Class not found."));
		return;
	}

	if (PatrolBotClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PatrolBot Class not found."));
		return;
	}
	//

	FVector HealerPosition = GetMesh()->GetComponentLocation();
	FVector PatrolPosition = GetMesh()->GetComponentLocation();

	HealerPosition.X += 20; //Meh
	PatrolPosition.X += 20; //Garbage
	PatrolPosition.Y += 20; //Garbage

	GetWorld()->SpawnActor<AHealerBot>(HealerClass, HealerPosition, GetMesh()->GetComponentRotation());
	GetWorld()->SpawnActor<APatrolBot>(PatrolBotClass, PatrolPosition, GetMesh()->GetComponentRotation());

}

void ACardsAndGunsCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ACardsAndGunsCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ACardsAndGunsCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ACardsAndGunsCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

