// Copyright (c) 2024 Felix Wahl (https://github.com/goldbarth). Provided under the MIT License. Full text: https://opensource.org/licenses/MIT

#include "OrbitDebug.h"

#include "OrbitDrawComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SolarSystem/Structs/Universe.h"

AOrbitDebug::AOrbitDebug()
{
	PrimaryActorTick.bCanEverTick = true;
	OrbitDrawComponent = CreateDefaultSubobject<UOrbitDrawComponent>(TEXT("DebugDraw"));
	RootComponent = OrbitDrawComponent;
}

void AOrbitDebug::DrawOrbitPaths()
{
	const UWorld* World = GetWorld();
	if (World == nullptr) return;
	
	TArray<AActor*> Bodies;
	UGameplayStatics::GetAllActorsOfClass(World, ACelestialBody::StaticClass(), Bodies);
	if (Bodies.Num() == 0) return;
	
	TArray<FVector> DrawPoints;
	DrawPoints.SetNum(Bodies.Num() * GetNumSteps());
	TArray<FVirtualBody> VirtualBodies = InitializeVirtualBodies(Bodies);

	SimulateOrbits(VirtualBodies, DrawPoints);
	DrawPaths(VirtualBodies, DrawPoints, Bodies);
}

TArray<FVirtualBody> AOrbitDebug::InitializeVirtualBodies(const TArray<AActor*>& Bodies)
{
	TArray<FVirtualBody> VirtualBodies;
	VirtualBodies.Reserve(Bodies.Num());
	
	for (const auto& Body : Bodies)
	{
		ACelestialBody* CelestialBody = Cast<ACelestialBody>(Body);
		if (CelestialBody)
		{
			VirtualBodies.Add(FVirtualBody(CelestialBody));
		}
	}
	
	return VirtualBodies;
}

void AOrbitDebug::SimulateOrbits(TArray<FVirtualBody>& VirtualBodies, TArray<FVector>& DrawPoints) const
{
	for (int Step = 0; Step < GetNumSteps(); ++Step)
	{
		UpdateVelocities(VirtualBodies);
		UpdatePositions(VirtualBodies, DrawPoints, Step);
	}
}

void AOrbitDebug::UpdateVelocities(TArray<FVirtualBody>& VirtualBodies) const
{
	for (int i = 0; i < VirtualBodies.Num(); ++i)
	{
		VirtualBodies[i].Velocity += CalculateAcceleration(i, VirtualBodies) * GetTimeStep();
	}
}

void AOrbitDebug::UpdatePositions(TArray<FVirtualBody>& VirtualBodies, TArray<FVector>& DrawPoints, const int& Step) const
{
	for (int i = 0; i < VirtualBodies.Num(); ++i)
	{
		VirtualBodies[i].Location += VirtualBodies[i].Velocity * GetTimeStep();
		DrawPoints[i * GetNumSteps() + Step] = VirtualBodies[i].Location;
	}
}

void AOrbitDebug::DrawPaths(const TArray<FVirtualBody>& VirtualBodies, const TArray<FVector>& DrawPoints, TArray<AActor*> Bodies) const
{
	for (int i = 0; i < VirtualBodies.Num(); ++i)
	{
		const ACelestialBody* CelestialBody = Cast<ACelestialBody>(Bodies[i]);
		FColor PathColor = CelestialBody->GetLineColor().ToFColor(true);
		if (CelestialBody == nullptr || CelestialBody->ActorHasTag(CentralBodyTag)) continue;
		for (int Steps = 0; Steps < GetNumSteps() - 1; ++Steps)
		{
			FVector Point = DrawPoints[i * GetNumSteps() + Steps];
			DrawDebugPoint(GetWorld(), Point, GetLineThickness(), PathColor, false, -1.0f);
		}
	}
}

FVector AOrbitDebug::CalculateAcceleration(const int& BodyIndex, const TArray<FVirtualBody>& VirtualBodies) const
{
	FVector Acceleration = FVector::ZeroVector;

	for (int i = 0; i < VirtualBodies.Num(); ++i)
	{
		if(BodyIndex != i)
		{
			const FVector Direction = VirtualBodies[i].Location - VirtualBodies[BodyIndex].Location;
			const float Distance = Direction.Size();
			const float Force = FUniverse::GravitationalConstant * VirtualBodies[i].Mass * VirtualBodies[BodyIndex].Mass / (Distance * Distance);
			Acceleration += Direction.GetSafeNormal() * (Force / VirtualBodies[BodyIndex].Mass);
		}
	}
	
	return Acceleration;
}

