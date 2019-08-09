// Cards&Guns 2019

using UnrealBuildTool;
using System.Collections.Generic;

public class CardsAndGunsTarget : TargetRules
{
	public CardsAndGunsTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		ExtraModuleNames.Add("CardsAndGuns");
	}
}
