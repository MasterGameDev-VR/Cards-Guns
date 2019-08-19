// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolBot.h"
#include "PatrolBotAiController.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APatrolBot::APatrolBot()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemyMeshAsset(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimationObj(TEXT("AnimBlueprint'/Game/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP'"));

	GetMesh()->SetSkeletalMesh(EnemyMeshAsset.Object);
	GetMesh()->bCastDynamicShadow = false;
	GetMesh()->CastShadow = false;

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	GetMesh()->SetAnimInstanceClass(AnimationObj.Object->GeneratedClass);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCharacterMovement()->MaxWalkSpeed = 300.0f;

	AIControllerClass = APatrolBotAiController::StaticClass();

}

// Called when the game starts or when spawned
void APatrolBot::BeginPlay()
{
	Super::BeginPlay();

	// TODO Chiudere tutto dentro un metodo
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), AllWayPoints);

	for (int i = 0; i < AllWayPoints.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("%f %s"), FVector::Dist(GetActorLocation(), AllWayPoints[i]->GetActorLocation()), *AllWayPoints[i]->GetName());
		
		if (FVector::Dist(GetActorLocation(), AllWayPoints[i]->GetActorLocation()) < range)
		{
			WayPoints.Add(AllWayPoints[i]);
		}
	}
	//
}

// Called every frame
void APatrolBot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(), GetMesh()->GetComponentLocation(), range, 8, FColor::Blue, false, 0.05f);

}

// Called to bind functionality to input
void APatrolBot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

