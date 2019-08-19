// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PatrolBot.generated.h"

UCLASS()
class CARDSANDGUNS_API APatrolBot : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APatrolBot();

	UPROPERTY(EditAnywhere, Category = WayPoints)
	TArray<AActor*> WayPoints;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:

	TArray<AActor*> AllWayPoints;

	float range = 1330.0f;

};
