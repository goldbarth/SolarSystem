// Copyright Epic Games, Inc. All Rights Reserved.

#include "OrbitDebugDisplayCommands.h"

#define LOCTEXT_NAMESPACE "FOrbitDebugDisplayModule"

void FOrbitDebugDisplayCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "OrbitDebugDisplay", "Bring up OrbitDebugDisplay window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
