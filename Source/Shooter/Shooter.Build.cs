// Shooter Game. All Rights Reserved.

using UnrealBuildTool;

public class Shooter : ModuleRules
{
	public Shooter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"Niagara",
			"GameplayTasks",
			"NavigationSystem",
			"PhysicsCore",
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"GameplayCameras"
		});
		
		PublicIncludePaths.AddRange(new string[] { 
			"Shooter/Public/Player", 
			"Shooter/Public/Components", 
			"Shooter/Public/Dev",
            "Shooter/Public/Weapon",
            "Shooter/Public/UI",
            "Shooter/Public/Animations",
            "Shooter/Public/Pickups",
            "Shooter/Public/Weapon/Components",
            "Shooter/Public/AI",
            "Shooter/Public/AI/Tasks",
            "Shooter/Public/AI/Services",
            "Shooter/Public/AI/EQS",
            "Shooter/Public/AI/Decorators",
            "Shooter/Public/Menu",
            "Shooter/Public/Menu/UI",
            "Shooter/Public/Sound",
        });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
