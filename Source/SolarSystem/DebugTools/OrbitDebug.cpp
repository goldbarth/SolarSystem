// Copyright (c) 2024 Felix Wahl (https://github.com/goldbarth). Provided under the MIT License. Full text: https://opensource.org/licenses/MIT

#include "OrbitDebug.h"

#include "OrbitDrawComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SolarSystem/Defines/Debug.h"
#include "SolarSystem/Structs/Universe.h"

AOrbitDebug::AOrbitDebug()
{
	PrimaryActorTick.bCanEverTick = true;
	OrbitDrawComponent = CreateDefaultSubobject<UOrbitDrawComponent>(TEXT("DebugDrawComponent"));
	RootComponent = OrbitDrawComponent;
}

void AOrbitDebug::StartOrbitDebugger()
{
	if (bOrbitChanged)
	{
		SimulateOrbits();
		bOrbitChanged = false;
	}

	if (bDrawOrbitPaths) DrawDebugPaths();
}

void AOrbitDebug::SimulateOrbits()
{
	if (!GetAllCelestialBodies()) return;
	if (!SetPoints()) return;
	InitializeVirtualBodies();
	CalculateOrbits();
}

bool AOrbitDebug::GetAllCelestialBodies()
{
	const UWorld* World = GetWorld();
	if (World == nullptr) return false;
	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(World, ACelestialBody::StaticClass(), FoundActors);
	Bodies = ConvertToWeakObjectPtrArray(FoundActors);
	return true;
}

bool AOrbitDebug::SetPoints()
{
	if (Bodies.Num() == 0) return false;
	Points.SetNum(Bodies.Num() * GetNumSteps());
	return true;
}

void AOrbitDebug::InitializeVirtualBodies()
{
	VirtualBodies.Empty();
	VirtualBodies.Reserve(Bodies.Num());
	
	for (const auto& Body : Bodies)
	{
		if (Body.IsValid())
		{
			VirtualBodies.Add(FVirtualBody(Body));
		}
	}
}

void AOrbitDebug::CalculateOrbits() 
{
	for (int Step = 0; Step < GetNumSteps(); ++Step)
	{
		UpdateVelocities();
		UpdatePositions(Step);
	}
}

void AOrbitDebug::UpdateVelocities()
{
	for (int i = 0; i < VirtualBodies.Num(); ++i)
	{
		VirtualBodies[i].Velocity += CalculateAcceleration(i) * GetTimeStep();
	}
}

void AOrbitDebug::UpdatePositions(const int& Step)
{
	for (int i = 0; i < VirtualBodies.Num(); ++i)
	{
		VirtualBodies[i].Location += VirtualBodies[i].Velocity * GetTimeStep();
		Points[i * GetNumSteps() + Step] = VirtualBodies[i].Location;
	}
}

void AOrbitDebug::DrawDebugPaths() const
{
	const int Steps = GetNumSteps();
	const float Thickness = GetLineThickness();
	for (int i = 0; i < VirtualBodies.Num(); ++i)
	{
		for (int Step = 0; Step < Steps - 1; ++Step)
		{
			FVector Point = Points[i * Steps + Step];
			DrawDebugPoint(GetWorld(), Point, Thickness,
				VirtualBodies[i].LineColor.ToFColor(true), false, -1.0f);
		}
	}
}

{
	{
		{
		}
	}
}

FVector AOrbitDebug::CalculateAcceleration(const int& BodyIndex) const
{
	FVector Acceleration = FVector::ZeroVector;

	for (int i = 0; i < VirtualBodies.Num(); ++i)
	{
		if(BodyIndex != i)
		{
			const FVector Direction = VirtualBodies[i].Location - VirtualBodies[BodyIndex].Location;
			const float Distance = FVector::Dist(VirtualBodies[i].Location, VirtualBodies[BodyIndex].Location);
			const float DistanceSquared = Distance * Distance;
			Acceleration += Direction.GetSafeNormal() * (FUniverse::GravitationalConstant * VirtualBodies[i].Mass) / DistanceSquared;
		}
	}
	
	return Acceleration;
}

TArray<TWeakObjectPtr<ACelestialBody>> AOrbitDebug::ConvertToWeakObjectPtrArray(const TArray<AActor*>& ActorArray) const
{
	TArray<TWeakObjectPtr<ACelestialBody>> WeakPtrArray;
	WeakPtrArray.Reserve(ActorArray.Num());

	for (auto* Actor : ActorArray)
	{
		ACelestialBody* CelestialBody = Cast<ACelestialBody>(Actor);
		if (CelestialBody != nullptr)
		{
			WeakPtrArray.Add(CelestialBody);
		}
	}

	return WeakPtrArray;
}

void AOrbitDebug::DeactivateSplineDebugDraw()
{
	for (auto* Spline : SplineComponents)
	{
		Spline->SetDrawDebug(false);
	}
}

