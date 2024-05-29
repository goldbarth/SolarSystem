// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "OrbitDebugDisplayStyle.h"

class FOrbitDebugDisplayCommands : public TCommands<FOrbitDebugDisplayCommands>
{
public:

	FOrbitDebugDisplayCommands()
		: TCommands<FOrbitDebugDisplayCommands>(TEXT("OrbitDebugDisplay"), NSLOCTEXT("Contexts", "OrbitDebugDisplay", "OrbitDebugDisplay Plugin"), NAME_None, FOrbitDebugDisplayStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};