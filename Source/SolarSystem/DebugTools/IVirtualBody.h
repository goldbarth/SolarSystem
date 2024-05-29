// Copyright (c) 2024 Felix Wahl (https://github.com/goldbarth). Provided under the MIT License. Full text: https://opensource.org/licenses/MIT

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IVirtualBody.generated.h"

UINTERFACE(MinimalAPI)
class UVirtualBody : public UInterface
{
	GENERATED_BODY()
};

/**
 * This class is responsible for drawing the orbits of celestial bodies.
 * It is the interface for the OrbitDebug class and OrbitDrawComponent class.
 */
class SOLARSYSTEM_API IVirtualBody
{
	GENERATED_BODY()

public:
	bool bUseTaskGraph = false;
	
	virtual bool GetDrawOrbitPaths() const = 0;
	virtual void StartOrbitDebugger() = 0;
};
