// Copyright (c) 2024 Felix Wahl (https://github.com/goldbarth). Provided under the MIT License. Full text: https://opensource.org/licenses/MIT


#include "OrbitDrawComponent.h"

UOrbitDrawComponent::UOrbitDrawComponent() : OrbitDrawer(Cast<IVirtualBody>(GetOwner()))
{
	PrimaryComponentTick.bCanEverTick = true;
	bTickInEditor = true;
}

void UOrbitDrawComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DrawOrbits();
}

void UOrbitDrawComponent::DrawOrbits() const
{
	if (OrbitDrawer)
	{
		OrbitDrawer->StartOrbitDebugger();
	}
}


