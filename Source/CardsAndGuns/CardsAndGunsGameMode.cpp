// Cards&Guns 2019

#include "CardsAndGunsGameMode.h"
#include "CardsAndGunsHUD.h"
#include "CardsAndGunsCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACardsAndGunsGameMode::ACardsAndGunsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ACardsAndGunsHUD::StaticClass();
}
