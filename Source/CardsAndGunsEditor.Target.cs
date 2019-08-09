// Cards&Guns 2019

using UnrealBuildTool;
using System.Collections.Generic;

public class CardsAndGunsEditorTarget : TargetRules
{
	public CardsAndGunsEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("CardsAndGuns");
	}
}
