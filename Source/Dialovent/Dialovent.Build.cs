// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Dialovent : ModuleRules
{
	public Dialovent(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
            "GameplayTags"
        });

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Dialovent",
			"Dialovent/Variant_Platforming",
			"Dialovent/Variant_Platforming/Animation",
			"Dialovent/Variant_Combat",
			"Dialovent/Variant_Combat/AI",
			"Dialovent/Variant_Combat/Animation",
			"Dialovent/Variant_Combat/Gameplay",
			"Dialovent/Variant_Combat/Interfaces",
			"Dialovent/Variant_Combat/UI",
			"Dialovent/Variant_SideScrolling",
			"Dialovent/Variant_SideScrolling/AI",
			"Dialovent/Variant_SideScrolling/Gameplay",
			"Dialovent/Variant_SideScrolling/Interfaces",
			"Dialovent/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
