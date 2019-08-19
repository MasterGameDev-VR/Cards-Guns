// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "PatrolTask.generated.h"

/**
 * 
 */
UCLASS()
class CARDSANDGUNS_API UPatrolTask : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, Category = WayPoints)
	struct FBlackboardKeySelector WayPointsIndex;

	UPROPERTY(EditAnywhere, Category = WayPoints)
	struct FBlackboardKeySelector WayPointsObject;
	
};
