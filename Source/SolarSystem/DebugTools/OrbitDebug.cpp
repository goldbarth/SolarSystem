// Copyright (c) 2024 Felix Wahl (https://github.com/goldbarth). Provided under the MIT License. Full text: https://opensource.org/licenses/MIT

#include "OrbitDebug.h"

#include "OrbitDrawComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SolarSystem/Structs/Universe.h"

AOrbitDebug::AOrbitDebug()
{
	PrimaryActorTick.bCanEverTick = true;
	OrbitDrawComponent = CreateDefaultSubobject<UOrbitDrawComponent>(TEXT("DebugDrawComponent"));
	RootComponent = OrbitDrawComponent;
}

void AOrbitDebug::DrawOrbitPaths()
{
	if (bHasChanged)
	{
		const UWorld* World = GetWorld();
		if (World == nullptr) return;
		
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(World, ACelestialBody::StaticClass(), FoundActors);
		Bodies = ConvertToWeakObjectPtrArray(FoundActors);
		
		if (Bodies.Num() == 0) return;
		
		Points.SetNum(Bodies.Num() * GetNumSteps());
		
		InitializeVirtualBodies(VirtualBodies, Bodies);
		SimulateOrbits(VirtualBodies, Points);
	
		bHasChanged = false;
	}
	
	DrawPaths(VirtualBodies, Points);
}

void AOrbitDebug::InitializeVirtualBodies(TArray<FVirtualBody>& OutVirtualBodies, const TArray<TWeakObjectPtr<ACelestialBody>>& DrawBodies)
{
	OutVirtualBodies.Empty();
	OutVirtualBodies.Reserve(DrawBodies.Num());
	
	for (const auto& Body : DrawBodies)
	{
		if (Body.IsValid())
		{
			OutVirtualBodies.Add(FVirtualBody(Body));
		}
	}
}

void AOrbitDebug::SimulateOrbits(TArray<FVirtualBody>& InVirtualBodies, TArray<FVector>& DrawPoints) const
{
	for (int Step = 0; Step < GetNumSteps(); ++Step)
	{
		UpdateVelocities(InVirtualBodies);
		UpdatePositions(InVirtualBodies, DrawPoints, Step);
	}
}

void AOrbitDebug::UpdateVelocities(TArray<FVirtualBody>& InVirtualBodies) const
{
	for (int i = 0; i < InVirtualBodies.Num(); ++i)
	{
		InVirtualBodies[i].Velocity += CalculateAcceleration(i, InVirtualBodies) * GetTimeStep();
	}
}

void AOrbitDebug::UpdatePositions(TArray<FVirtualBody>& InVirtualBodies, TArray<FVector>& DrawPoints, const int& Step) const
{
	for (int i = 0; i < InVirtualBodies.Num(); ++i)
	{
		InVirtualBodies[i].Location += InVirtualBodies[i].Velocity * GetTimeStep();
		DrawPoints[i * GetNumSteps() + Step] = InVirtualBodies[i].Location;
	}
}

void AOrbitDebug::DrawPaths(const TArray<FVirtualBody>& InVirtualBodies, const TArray<FVector>& DrawPoints) const
{
	const int NumSteps = GetNumSteps();
	for (int i = 0; i < InVirtualBodies.Num(); ++i)
	{
		const ACelestialBody* CelestialBody = Cast<ACelestialBody>(Bodies[i]);
		FColor PathColor = CelestialBody->GetLineColor().ToFColor(true);
		if (CelestialBody == nullptr || CelestialBody->ActorHasTag(CentralBodyTag)) continue;
		for (int Steps = 0; Steps < NumSteps - 1; ++Steps)
		{
			FVector Point = DrawPoints[i * NumSteps + Steps];
			DrawDebugPoint(GetWorld(), Point, GetLineThickness(), PathColor, false, -1.0f);
		}
	}
}

FVector AOrbitDebug::CalculateAcceleration(const int& BodyIndex, const TArray<FVirtualBody>& InVirtualBodies) const
{
	FVector Acceleration = FVector::ZeroVector;

	for (int i = 0; i < InVirtualBodies.Num(); ++i)
	{
		if(BodyIndex != i)
		{
			const FVector Direction = InVirtualBodies[i].Location - InVirtualBodies[BodyIndex].Location;
			const float Distance = FVector::Dist(InVirtualBodies[i].Location, InVirtualBodies[BodyIndex].Location);
			const float DistanceSquared = Distance * Distance;
			Acceleration += Direction.GetSafeNormal() * (FUniverse::GravitationalConstant * InVirtualBodies[i].Mass) / DistanceSquared;
		}
	}
	
	return Acceleration;
}

TArray<TWeakObjectPtr<ACelestialBody>> AOrbitDebug::ConvertToWeakObjectPtrArray(const TArray<AActor*>& ActorArray) const
{
	TArray<TWeakObjectPtr<ACelestialBody>> WeakPtrArray;
	WeakPtrArray.Reserve(ActorArray.Num());

	for (AActor* Actor : ActorArray)
	{
		if (ACelestialBody* CelestialBody = Cast<ACelestialBody>(Actor))
		{
			WeakPtrArray.Add(CelestialBody);
		}
	}

	return WeakPtrArray;
}

