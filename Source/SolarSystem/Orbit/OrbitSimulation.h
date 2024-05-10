// Author (c) 2024 Felix Wahl (https://github.com/goldbarth). Provided under the MIT License. Full text: https://opensource.org/licenses/MIT

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ACelestialBodyRegistry.h"
#include "SolarSystem/CelestialBody/CelestialBody.h"
#include "OrbitSimulation.generated.h"

/**
 * This class is responsible for simulating the orbits of celestial bodies.
 */
UCLASS()
class SOLARSYSTEM_API AOrbitSimulation : public AActor
{
	GENERATED_BODY()

public:
	AOrbitSimulation();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
	bool bManualTimeScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
	float TimeScale;

	UPROPERTY()
	ACelestialBodyRegistry* CelestialBodyRegistry;
private:

	void UpdateAllObjects(const float& TimeStep) const;
	void UpdateAllPositions(const float& TimeStep) const;
	void UpdateAllVelocities(const float& TimeStep) const;

	FVector CalculateGravitationalAcceleration(const FVector& OtherPosition, const ACelestialBody* Object) const;
	
	void GetCelestialObjectManager();
};
