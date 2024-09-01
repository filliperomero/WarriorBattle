// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class WarriorBattle : ModuleRules
{
	public WarriorBattle(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GameplayAbilities", "UMG", "AIModule", "MotionWarping", "Niagara", "NavigationSystem" });

		PrivateDependencyModuleNames.AddRange(new string[] { "GameplayTags", "GameplayTasks", "AIModule", "AnimGraphRuntime" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
