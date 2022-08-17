// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class UnrealSampleXRTarget : TargetRules
{
	public UnrealSampleXRTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "UnrealSampleXR" } );
        
        bOverrideBuildEnvironment = true;
        AdditionalCompilerArguments = "-Wno-unused-but-set-variable";
	}
}
