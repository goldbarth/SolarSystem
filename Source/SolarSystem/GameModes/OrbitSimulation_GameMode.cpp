// Author (c) 2024 Felix Wahl (https://github.com/goldbarth). Provided under the MIT License. Full text: https://opensource.org/licenses/MIT


#include "OrbitSimulation_GameMode.h"

#include "../Defines/Debug.h"

void AOrbitSimulation_GameMode::StartPlay()
{
	Super::StartPlay();
	
	Initialize();
}

void AOrbitSimulation_GameMode::Initialize()
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
