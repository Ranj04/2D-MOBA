using UnrealBuildTool;
public class AetherArena : ModuleRules {
    public AetherArena(ReadOnlyTargetRules Target) : base(Target) {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new[] {
            "Core","CoreUObject","Engine","InputCore","Paper2D",
            "OnlineSubsystem","OnlineSubsystemUtils","GameplayAbilities","GameplayTasks","AIModule","UMG"
        });
        PrivateDependencyModuleNames.AddRange(new[] { "Slate","SlateCore" });
        DynamicallyLoadedModuleNames.Add("OnlineSubsystemEOS");
    }
}
