// Cards&Guns 2019

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CardsAndGunsHUD.generated.h"

UCLASS()
class ACardsAndGunsHUD : public AHUD
{
	GENERATED_BODY()

public:
	ACardsAndGunsHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

