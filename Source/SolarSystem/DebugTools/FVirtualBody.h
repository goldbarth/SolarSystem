// Copyright (c) 2024 Felix Wahl (https://github.com/goldbarth). Provided under the MIT License. Full text: https://opensource.org/licenses/MIT

#pragma once

#include "SolarSystem/CelestialBody/CelestialBody.h"

/**
 * A virtual body is a representation of a celestial body that is used for calculations.
 */
struct FVirtualBody
{
	float Mass;

	FVector Location;
	FVector Velocity;

	explicit FVirtualBody(const TWeakObjectPtr<ACelestialBody>& Body)
	{
		if (Body.IsValid())
		{
			Mass = Body->GetMass();
			Location = Body->GetActorLocation();
			Velocity = Body->GetInitialVelocity();
		}
	}
};
