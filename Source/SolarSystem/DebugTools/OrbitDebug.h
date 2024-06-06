// Copyright (c) 2024 Felix Wahl (https://github.com/goldbarth). Provided under the MIT License. Full text: https://opensource.org/licenses/MIT

#pragma once

#include "CoreMinimal.h"
#include "FVirtualBody.h"
#include "IVirtualBody.h"
#include "OrbitDrawComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "OrbitDebug.generated.h"

/**
 * This class is responsible for drawing the orbits of celestial bodies in the editor.
 */
UCLASS()
class SOLARSYSTEM_API AOrbitDebug : public AActor, public IVirtualBody
{
	GENERATED_BODY()

protected:
	AOrbitDebug();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	
	UPROPERTY(VisibleAnywhere)
	UOrbitDrawComponent* OrbitDrawComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbit Debug")
	UStaticMesh* SplineMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbit Debug")
	bool bDrawOrbitPaths;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbit Debug")
	bool bDrawSplines;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbit Debug")
	float LineThickness = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbit Debug")
	int NumSteps = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbit Debug")
	float TimeStep = 500.0f;

public:
	
#pragma region Getters and Setters
	
	virtual bool GetDrawOrbitPaths() const override { return bDrawOrbitPaths; }
	void SetDrawOrbitPaths(const bool& bNewDrawOrbitPaths) { bDrawOrbitPaths = bNewDrawOrbitPaths; UpdateOrbitChanged(true); }

	bool GetDrawSplines() const { return bDrawSplines; }
	void SetDrawSplines(const bool& bNewDrawSplines) { bDrawSplines = bNewDrawSplines; UpdateOrbitChanged(true); }
	
	float GetLineThickness() const { return LineThickness; }
	void SetLineThickness(const float& NewLineThickness) { LineThickness = NewLineThickness; UpdateOrbitChanged(true); }

	int GetNumSteps() const { return NumSteps; }
	void SetNumSteps(const int& NewNumSteps) { NumSteps = NewNumSteps; UpdateOrbitChanged(true); }

	float GetTimeStep() const { return TimeStep; }
	void SetTimeStep(const float& NewTimeStep) { TimeStep = NewTimeStep; UpdateOrbitChanged(true); }

	void UpdateOrbitChanged(const bool& bNewHasChanged) { bOrbitChanged = bNewHasChanged; }

#pragma endregion
	
	virtual void RunOrbitDebugger() override;

private:
	UPROPERTY()
	TArray<USplineComponent*> SplineComponents;
	UPROPERTY()
	TArray<TWeakObjectPtr<ACelestialBody>> Bodies;
	
	TArray<FVirtualBody> VirtualBodies;
	TArray<FVector> Points;
	bool bOrbitChanged = true;

	void SimulateOrbits();
	bool SetPoints();
	bool GetAllCelestialBodies();
	void InitializeVirtualBodies();
	
	void CalculateOrbits();
	void UpdateVelocities();
	void UpdatePositions(const int& Step);
	void RungeKuttaIntegration(int Step);
	
	FVector CalculateAcceleration(int BodyIndex, const FVector& TempPosition) const;
	FVector CalculateAcceleration(const int& BodyIndex) const;
	void DrawDebugPaths() const;
	void AddSplineComponents();
	void AddSegmentPoints();
	void ClearSplinePoints();
	void DrawSplinePaths();
	

	TArray<TWeakObjectPtr<ACelestialBody>> ConvertToWeakObjectPtrArray(const TArray<AActor*>& ActorArray) const;
	void DeactivateSplineDebugDraw();
};
