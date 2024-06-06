// Author (c) 2024 Felix Wahl (https://github.com/goldbarth). Provided under the MIT License. Full text: https://opensource.org/licenses/MIT


#include "OrbitSimulation_GameMode.h"

#include "../Defines/Debug.h"

AOrbitSimulation_GameMode::AOrbitSimulation_GameMode(): OrbitSimulation(nullptr), CelestialBodyRegistry(nullptr)
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(
		TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassFinder(
		TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonPlayerController"));
	if (PlayerPawnClassFinder.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnClassFinder.Class;
	}
	else
	{
		LOG_WARNING("Failed to find PlayerPawn class!")
		DefaultPawnClass = APawn::StaticClass();
	}
	if (PlayerControllerClassFinder.Class != nullptr)
	{
		PlayerControllerClass = PlayerControllerClassFinder.Class;
	}
	else
	{
		LOG_WARNING("Failed to find PlayerController class!")
		PlayerControllerClass = APlayerController::StaticClass();
	}
}

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
			LOG_WARNING("Failed to create CelestialObjectRegistry!")
		}
		else
		{
			LOG_DISPLAY("Created CelestialObjectRegistry!")
		}
		OrbitSimulation = World->SpawnActor<AOrbitSimulation>();
		if (!OrbitSimulation)
		{
			LOG_ERROR("Failed to create OrbitSimulation!")
		}
		else
		{
			LOG_DISPLAY("Created OrbitSimulation!")
		}
	}
}
