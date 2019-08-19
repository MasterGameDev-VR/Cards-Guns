// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "PatrolBotAiController.generated.h"

/**
 * 
 */
UCLASS()
class CARDSANDGUNS_API APatrolBotAiController : public AAIController
{
	GENERATED_BODY()

		
public:

	APatrolBotAiController();

	virtual void BeginPlay() override;

private:

	UBehaviorTree* PatrolTree;
	
};
