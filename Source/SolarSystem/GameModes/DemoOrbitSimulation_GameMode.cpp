// Author (c) 2024 Felix Wahl (https://github.com/goldbarth). Provided under the MIT License. Full text: https://opensource.org/licenses/MIT


#include "DemoOrbitSimulation_GameMode.h"

#include "../Defines/Debug.h"

void ADemoOrbitSimulation_GameMode::StartPlay()
{
	Super::StartPlay();
	
	InitializeSimulation();
}

void ADemoOrbitSimulation_GameMode::InitializeSimulation()
{
	UWorld* World = GetWorld();
	if (World)
	{
		CelestialBodyRegistry = World->SpawnActor<ACelestialBodyRegistry>();
		if (!CelestialBodyRegistry)
		{
			LOG_WARNING("Failed to create CelestialObjectManager! (DemoOrbitSimulation_GameMode)")
		}
		else
		{
			LOG_DISPLAY("Created CelestialObjectManager! (DemoOrbitSimulation_GameMode)")
		}
		OrbitSimulation = World->SpawnActor<AOrbitSimulation>();
		if (!OrbitSimulation)
		{
			LOG_ERROR("Failed to create OrbitSimulation! (DemoOrbitSimulation_GameMode)")
		}
		else
		{
			LOG_DISPLAY("Created OrbitSimulation! (DemoOrbitSimulation_GameMode)")
		}
	}
}
