// Copyright (c) 2024 Felix Wahl (https://github.com/goldbarth). Provided under the MIT License. Full text: https://opensource.org/licenses/MIT

#include "OrbitDebug.h"

#include "OrbitDrawComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SolarSystem/Defines/Debug.h"
#include "SolarSystem/Structs/Universe.h"

AOrbitDebug::AOrbitDebug()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Root->SetMobility(EComponentMobility::Static);
	RootComponent = Root;
	
	OrbitDrawComponent = CreateDefaultSubobject<UOrbitDrawComponent>(TEXT("DebugDrawComponent"));
	OrbitDrawComponent->SetupAttachment(Root);
}

void AOrbitDebug::RunOrbitDebugger()
{
	if (bOrbitChanged)
	{
		SimulateOrbits();
		bOrbitChanged = false;
	}

	if (bDrawOrbitPaths) DrawDebugPaths();
	bDrawSplines ? DrawSplinePaths() : DeactivateSplineDebugDraw();
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
		// UpdateVelocities();
		// UpdatePositions(Step);
		RungeKuttaIntegration(Step);
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

void AOrbitDebug::RungeKuttaIntegration(const int Step)
{
	const float h = GetTimeStep();
	TArray<FVector> NewPositions;
	TArray<FVector> NewVelocities;
	NewPositions.SetNum(VirtualBodies.Num());
	NewVelocities.SetNum(VirtualBodies.Num());

	for (int i = 0; i < VirtualBodies.Num(); ++i)
	{
		FVector Position = VirtualBodies[i].Location;
		FVector Velocity = VirtualBodies[i].Velocity;

		FVector K1 = h * Velocity;
		FVector L1 = h * CalculateAcceleration(i, Position);

		FVector K2 = h * (Velocity + 0.5f * L1);
		FVector L2 = h * CalculateAcceleration(i, Position + 0.5f * K1);

		FVector K3 = h * (Velocity + 0.5f * L2);
		FVector L3 = h * CalculateAcceleration(i, Position + 0.5f * K2);

		FVector K4 = h * (Velocity + L3);
		FVector L4 = h * CalculateAcceleration(i, Position + K3);

		NewPositions[i] = Position + (K1 + 2.0f * K2 + 2.0f * K3 + K4) / 6.0f;
		NewVelocities[i] = Velocity + (L1 + 2.0f * L2 + 2.0f * L3 + L4) / 6.0f;
	}

	for (int i = 0; i < VirtualBodies.Num(); ++i)
	{
		VirtualBodies[i].Location = NewPositions[i];
		VirtualBodies[i].Velocity = NewVelocities[i];
		Points[i * GetNumSteps() + Step] = NewPositions[i];
	}
}

void AOrbitDebug::DrawDebugPaths() const
{
	const int NumBodies = VirtualBodies.Num();
	const int Steps = GetNumSteps();
	const float Thickness = GetLineThickness();
	
	if (bDrawSplines)
	{
		for (int i = 0; i < NumBodies; ++i)
		{
			for (int j = 1; j < Steps; ++j)
			{
				FVector Start = Points[i * Steps + (j - 1)];
				FVector End = Points[i * Steps + j];
				if (!Start.IsZero() && !End.IsZero())
				{
					FColor LineColor = VirtualBodies[i].LineColor.ToFColor(true);
					DrawDebugLine(GetWorld(), Start, End, LineColor, false, -1.0f, 0, Thickness);
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < NumBodies; ++i)
		{
			for (int j = 1; j < Steps; ++j)
			{
				FVector Point = Points[i * Steps + j];
				if (!Point.IsZero())
				{
					FColor LineColor = VirtualBodies[i].LineColor.ToFColor(true);
					DrawDebugPoint(GetWorld(), Point, Thickness, LineColor, false, -1.0f);
				}
			}
		}
	}
}

void AOrbitDebug::DrawSplinePaths()
{
	ClearSplinePoints();
	AddSplineComponents();
	AddSegmentPoints();
}

void AOrbitDebug::ClearSplinePoints()
{
	for (auto* Spline : SplineComponents)
	{
		Spline->ClearSplinePoints(false);
	}
}

void AOrbitDebug::AddSplineComponents()
{
	while (SplineComponents.Num() < VirtualBodies.Num())
	{
		USplineComponent* NewSpline = NewObject<USplineComponent>(this, USplineComponent::StaticClass());
		NewSpline->RegisterComponentWithWorld(GetWorld());
		NewSpline->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
		NewSpline->SetClosedLoop(false);
		SplineComponents.Add(NewSpline);
	}
}

void AOrbitDebug::AddSegmentPoints()
{
	const int Steps = GetNumSteps();
	for (int i = 0; i < VirtualBodies.Num(); ++i)
	{
		USplineComponent* Spline = SplineComponents[i];

		for (int Step = 0; Step < Steps; ++Step)
		{

			FVector Point = Points[i * Steps + Step];
			if (Point.ContainsNaN())
			{
				LOG_WARNING_F("Point contains NaN: %s", *Point.ToString());
				continue;
			}

			Spline->AddSplinePoint(Point, ESplineCoordinateSpace::World, false);
			Spline->SetSplinePointType(Spline->GetNumberOfSplinePoints() - 1, ESplinePointType::Curve, false);
		}
		
		Spline->UpdateSpline();
		
		Spline->SetDrawDebug(true);
		Spline->SetSelectedSplineSegmentColor(VirtualBodies[i].LineColor);
		Spline->SetUnselectedSplineSegmentColor(VirtualBodies[i].LineColor);
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

FVector AOrbitDebug::CalculateAcceleration(const int BodyIndex, const FVector& TempPosition) const
{
	FVector Acceleration = FVector::ZeroVector;
    
	for (int i = 0; i < VirtualBodies.Num(); ++i)
	{
		if (i != BodyIndex)
		{
			FVector Direction = VirtualBodies[i].Location - TempPosition;
			float Distance = Direction.Size();
			Direction.Normalize();
			Acceleration += (FUniverse::GravitationalConstant * VirtualBodies[i].Mass / (Distance * Distance)) * Direction;
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

