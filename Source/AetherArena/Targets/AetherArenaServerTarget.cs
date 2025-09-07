using UnrealBuildTool;
public class AetherArenaServerTarget : TargetRules {
    public AetherArenaServerTarget(TargetInfo Target) : base(Target) {
        Type = TargetType.Server; DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
        ExtraModuleNames.Add("AetherArena");
    }
}
