// Author (c) 2024 Felix Wahl (https://github.com/goldbarth). Provided under the MIT License. Full text: https://opensource.org/licenses/MIT


#include "OrbitSimulation.h"

#include "SolarSystem/GameModes/OrbitSimulation_GameMode.h"
#include "SolarSystem/Structs/Universe.h"
#include "ACelestialBodyRegistry.h"
#include "../Defines/Debug.h"


AOrbitSimulation::AOrbitSimulation(): bManualTimeScale(false), TimeScale(10.0f), CelestialBodyRegistry(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AOrbitSimulation::BeginPlay()
{
	Super::BeginPlay();

	GetCelestialBodyRegistry();
}

void AOrbitSimulation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	DeltaTime = FUniverse::TimeStep;
	const float ScaledDeltaTime = bManualTimeScale ? DeltaTime * TimeScale : DeltaTime;
	UpdateAllObjects(ScaledDeltaTime);
}

void AOrbitSimulation::UpdateAllObjects(const float& TimeStep) const
{
	if (CelestialBodyRegistry)
	{
		UpdateAllPositions(TimeStep);
		UpdateAllVelocities(TimeStep);
	}
	else
	{
		LOG_DISPLAY("CelestialObjectManager is nullptr!");
	}
	
}

void AOrbitSimulation::UpdateAllPositions(const float& TimeStep) const
{
	for (const auto& Body : CelestialBodyRegistry->GetCelestialObjects())
	{
		Body->UpdatePosition(TimeStep);
	}
}

void AOrbitSimulation::UpdateAllVelocities(const float& TimeStep) const
{
	for (const auto& Body : CelestialBodyRegistry->GetCelestialObjects())
	{
		FVector Acceleration = CalculateGravitationalAcceleration(Body->GetActorLocation(), Body);
		Body->UpdateVelocity(Acceleration, TimeStep);
	}
}

/**
 * Calculates the gravitational acceleration towards an object.
 *
 * This function calculates the gravitational acceleration vector pointing towards a specified celestial object.
 * It assumes the object is within a uniform gravitational field influenced by the specified object's mass.
 *
 * @param OtherPosition The position of the object experiencing the gravitational force.
 * @param Object The celestial object exerting the gravitational force.
 * @return FVector The calculated gravitational acceleration vector.
 */
FVector AOrbitSimulation::CalculateGravitationalAcceleration(const FVector& OtherPosition, const ACelestialBody* Object) const
{
	// If one mass is much larger than the other, it is convenient to take it as observational reference and define
	// it as source of a gravitational field of magnitude and orientation. The larger mass is virtually stationary.
	// The assumption for the calculation of the gravitational effect is used for smaller objects in the reference system.
	// The smaller mass moves under the influence of the gravitational field of the larger mass.
	// g = G * M / r^2 | Gravitational acceleration
	// https://en.wikipedia.org/wiki/Gravitational_acceleration | Details and history of the formula
	
	FVector Acceleration = FVector::ZeroVector;
	for (const auto& Obj : CelestialBodyRegistry->GetCelestialObjects())
	{
		if (Obj == Object) continue;

		// Gravitational constant G
		constexpr float G = FUniverse::GravitationalConstant;
		// Mass of the sample object m
		const float M = Obj->GetMass();
		// Distance between two objects r = |r1 - r2| r = R
		FVector R = Obj->GetActorLocation() - OtherPosition;
		// Distance squared
		const float SqrR = R.SizeSquared();
		// Direction of the force
		FVector ForceDir = R.GetSafeNormal();

		// Superposition of all gravitational forces:
		// The vectorial sum of all gravitational accelerations emanating from each object in the
		// field is formed to determine the total acceleration of the object under consideration.
		Acceleration += ForceDir * G * M / SqrR;
	}
	
	return Acceleration;
}

void AOrbitSimulation::GetCelestialBodyRegistry()
{
	AOrbitSimulation_GameMode* GameMode = Cast<AOrbitSimulation_GameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		CelestialBodyRegistry = GameMode->GetCelestialBodyRegistry();
		if (!CelestialBodyRegistry)
		{
			LOG_WARNING("Something went wrong! Failed to create CelestialBodyRegistry!")
		}
	}
	else
	{
		LOG_ERROR("Failed to cast Game Mode!")
	}
}