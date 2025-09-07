using UnrealBuildTool;
public class AetherArenaTarget : TargetRules {
    public AetherArenaTarget(TargetInfo Target) : base(Target) {
        Type = TargetType.Game; DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
        ExtraModuleNames.Add("AetherArena");
    }
}
