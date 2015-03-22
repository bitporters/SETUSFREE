

using UnrealBuildTool;
using System.Collections.Generic;

public class ServerTarget : TargetRules
{
    public ServerTarget(TargetInfo Target)
    {
        Type = TargetType.Server;
    }

    //
    // TargetRules interface.
    //

    public override void SetupBinaries(
        TargetInfo Target,
        ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
        ref List<string> OutExtraModuleNames
        )
    {
        OutExtraModuleNames.AddRange(new string[] { "SETUSFREE" });
    }

    public override void SetupGlobalEnvironment(
       TargetInfo Target,
       ref LinkEnvironmentConfiguration OutLinkEnvironmentConfiguration,
       ref CPPEnvironmentConfiguration OutCPPEnvironmentConfiguration
       )
    {
        if (UnrealBuildTool.UnrealBuildTool.BuildingRocket())
        {
            UEBuildConfiguration.bCompileLeanAndMeanUE = true;

            // Don't need editor or editor only data
            UEBuildConfiguration.bBuildEditor = false;
            UEBuildConfiguration.bBuildWithEditorOnlyData = false;

            UEBuildConfiguration.bCompileAgainstEngine = true;

            // no exports, so no need to verify that a .lib and .exp file was emitted by the linker.
            OutLinkEnvironmentConfiguration.bHasExports = false;
        }
        else
        {
            // Tag it as a UE4Game build
            OutCPPEnvironmentConfiguration.Definitions.Add("UE4GAME=1");
        }
    }

    public override bool GetSupportedPlatforms(ref List<UnrealTargetPlatform> OutPlatforms)
    {
        // It is valid for only server platforms
        return UnrealBuildTool.UnrealBuildTool.GetAllServerPlatforms(ref OutPlatforms, false);
    }

    public override List<UnrealTargetPlatform> GUBP_GetPlatforms_MonolithicOnly(UnrealTargetPlatform HostPlatform)
    {
        if (HostPlatform == UnrealTargetPlatform.Mac)
        {
            return new List<UnrealTargetPlatform>();
        }
        return new List<UnrealTargetPlatform> { HostPlatform, UnrealTargetPlatform.Win32, UnrealTargetPlatform.Linux };
    }

    public override List<UnrealTargetConfiguration> GUBP_GetConfigs_MonolithicOnly(UnrealTargetPlatform HostPlatform, UnrealTargetPlatform Platform)
    {
        return new List<UnrealTargetConfiguration> { UnrealTargetConfiguration.Development };
    }
}
