// Fill out your copyright notice in the Description page of Project Settings.


#include "HealerBot.h"
#include "Kismet/GameplayStatics.h"
#include "BotAiController.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AHealerBot::AHealerBot()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	/*EnemyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mannequin_Arms"));*/
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemyMeshAsset(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimationObj(TEXT("AnimBlueprint'/Game/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> MaterialAsset(TEXT("Material'/Game/FirstPerson/Meshes/FirstPersonProjectileMaterial.FirstPersonProjectileMaterial'"));

	GetMesh()->SetSkeletalMesh(EnemyMeshAsset.Object);
	GetMesh()->bCastDynamicShadow = false;
	GetMesh()->CastShadow = false;
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	GetMesh()->SetAnimInstanceClass(AnimationObj.Object->GeneratedClass);

	GetMesh()->SetMaterial(0, MaterialAsset.Object);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCharacterMovement()->MaxWalkSpeed = 300.0f;

	AIControllerClass = ABotAiController::StaticClass();


}

// Called when the game starts or when spawned
void AHealerBot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHealerBot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHealerBot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AHealerBot::heal(ACharacter * character)
{
	//TODO
}

