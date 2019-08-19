// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BotAiController.generated.h"

/**
 * 
 */
UCLASS()
class CARDSANDGUNS_API ABotAiController : public AAIController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	void SearchForPlayer();

private:

	FTimerHandle TimeHandler;
	
};
