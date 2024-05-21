// Author (c) 2024 Felix Wahl (https://github.com/goldbarth). Provided under the MIT License. Full text: https://opensource.org/licenses/MIT

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SolarSystem/Orbit/OrbitSimulation.h"
#include "SolarSystem/Orbit/ACelestialBodyRegistry.h"
#include "OrbitSimulation_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class SOLARSYSTEM_API AOrbitSimulation_GameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Celestial Objects")
	AOrbitSimulation* OrbitSimulation;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Celestial Objects")
	ACelestialBodyRegistry* CelestialBodyRegistry;


public:
	AOrbitSimulation* GetOrbitSimulation() const { return OrbitSimulation; }
	ACelestialBodyRegistry* GetCelestialBodyRegistry() const { return CelestialBodyRegistry; }

	virtual void StartPlay() override;
	
private:
	void Initialize();
	
};
