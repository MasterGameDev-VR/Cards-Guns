// Fill out your copyright notice in the Description page of Project Settings.


#include "BotAiController.h"
#include "Kismet/GameplayStatics.h"


void ABotAiController::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimeHandler, this, &ABotAiController::SearchForPlayer, 2.0f, true, 0.0f);
}

void ABotAiController::SearchForPlayer()
{
	APlayerController * PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	ACharacter * PlayerCharacter = PlayerController->GetCharacter();

	if (PlayerCharacter)
	{
		/*UE_LOG(LogTemp, Error, TEXT("IM FOLLOWING"));*/
		this->MoveToActor(PlayerController);
	}

}
