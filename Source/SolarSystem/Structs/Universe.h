#pragma once

#include "CoreMinimal.h"

struct FUniverse
{
	static constexpr float GravitationalConstant = 0.1f; // 6.67430e-11f | m^3 kg^-1 s^-2 (scaled down)
	static constexpr float TimeStep = 0.1f;
};
