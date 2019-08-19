// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "HealerBot.generated.h"

UCLASS()
class CARDSANDGUNS_API AHealerBot : public ACharacter
{
	GENERATED_BODY()


// 	UPROPERTY(VisibleDefaultsOnly, Category = EnemyMesh)
// 	class USkeletalMeshComponent* EnemyMesh;

public:
	// Sets default values for this character's properties
	AHealerBot();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void heal(ACharacter* character);

private:

	int health;
	int healthPerSecond;

};