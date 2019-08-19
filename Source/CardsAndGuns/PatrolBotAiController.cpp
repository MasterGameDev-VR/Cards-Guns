// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolBotAiController.h"

APatrolBotAiController::APatrolBotAiController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTOb(TEXT("BehaviorTree'/Game/AI/BehaviourTrees/PatrolBehaviour.PatrolBehaviour'"));
	PatrolTree = BTOb.Object;
}

void APatrolBotAiController::BeginPlay()
{
	Super::BeginPlay();

	if (PatrolTree)
	{
		RunBehaviorTree(PatrolTree);
	}
}
