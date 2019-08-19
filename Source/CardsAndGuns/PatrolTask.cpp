// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolTask.h"
#include "PatrolBot.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

EBTNodeResult::Type UPatrolTask::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	auto BlackBoard = OwnerComp.GetBlackboardComponent();	
	auto index = BlackBoard->GetValueAsInt(WayPointsIndex.SelectedKeyName);
	/*UE_LOG(LogTemp, Warning, TEXT("%i"), index);*/

	auto PatrolBot = Cast<APatrolBot>(OwnerComp.GetAIOwner()->GetPawn());
	auto WayPoints = PatrolBot->WayPoints;

	if (WayPoints.Num() == 0)
	{
		/*UE_LOG(LogTemp, Error, TEXT("No waypoints found"));*/
		return EBTNodeResult::Failed;
	}

	BlackBoard->SetValueAsObject(WayPointsObject.SelectedKeyName, WayPoints[index]);

	auto Next = (index + 1) % WayPoints.Num();
	BlackBoard->SetValueAsInt(WayPointsIndex.SelectedKeyName, Next);

	return EBTNodeResult::Succeeded;;
}
