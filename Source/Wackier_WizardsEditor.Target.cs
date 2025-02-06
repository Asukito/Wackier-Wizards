// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Wackier_WizardsEditorTarget : TargetRules
{
    public Wackier_WizardsEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.Latest;

        ExtraModuleNames.AddRange(new string[] { "Wackier_Wizards" });
    }
}
