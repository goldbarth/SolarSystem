// Author (c) 2024 Felix Wahl (https://github.com/goldbarth). Provided under the MIT License. Full text: https://opensource.org/licenses/MIT

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SolarSystem/CelestialBody/CelestialBody.h"
#include "ACelestialBodyRegistry.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCelestialObjectAddedDelegate, ACelestialBody*, CelestialObject);

/**
 * Manages all celestial bodies in the scene.
 */
UCLASS()
class SOLARSYSTEM_API ACelestialBodyRegistry : public AActor
{
	GENERATED_BODY()

public:
	ACelestialBodyRegistry();

	UPROPERTY(BlueprintAssignable)
	FCelestialObjectAddedDelegate OnCelestialBodyAdded;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Celestial Objects")
	TArray<ACelestialBody*> CelestialBodies;

public:
	UFUNCTION()
	void AddCelestialObject(ACelestialBody* CelestialObject);
	
	void RemoveCelestialObject(ACelestialBody* CelestialObject);
	
	TArray<ACelestialBody*> GetCelestialObjects() const { return CelestialBodies; }
};
