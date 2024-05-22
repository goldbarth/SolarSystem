// Copyright (c) 2024 Felix Wahl (https://github.com/goldbarth). Provided under the MIT License. Full text: https://opensource.org/licenses/MIT

#pragma once

#include "CoreMinimal.h"
#include "FVirtualBody.h"
#include "IVirtualBody.h"
#include "OrbitDrawComponent.h"
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
	
	UPROPERTY(VisibleDefaultsOnly)
	UOrbitDrawComponent* OrbitDrawComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbit Debug")
	bool bDrawOrbitPaths;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbit Debug")
	bool bUseTaskGraph;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbit Debug")
	float LineThickness = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbit Debug")
	int NumSteps = 35000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbit Debug")
	float TimeStep = 0.1f;
	
public:
	
#pragma region Getters and Setters
	
	virtual bool GetDrawOrbitPaths() const override { return bDrawOrbitPaths; }
	void SetDrawOrbitPaths(const bool& bNewDrawOrbitPaths) { bDrawOrbitPaths = bNewDrawOrbitPaths; }

	virtual bool GetUseTaskGraph() const override { return bUseTaskGraph; }
	void SetUseTaskGraph(const bool& bNewUseTaskGraph) { bUseTaskGraph = bNewUseTaskGraph; }

	float GetLineThickness() const { return LineThickness; }
	void SetLineThickness(const float& NewLineThickness) { LineThickness = NewLineThickness; }

	int GetNumSteps() const { return NumSteps; }
	void SetNumSteps(const int& NewNumSteps) { NumSteps = NewNumSteps; }

	float GetTimeStep() const { return TimeStep; }
	void SetTimeStep(const float& NewTimeStep) { TimeStep = NewTimeStep; }

#pragma endregion

	// Interface implementation
	virtual void DrawOrbitPaths() override;

private:
	const char* CentralBodyTag = "Center";

	TArray<FVirtualBody> InitializeVirtualBodies(const TArray<AActor*>& Bodies);
	void SimulateOrbits(TArray<FVirtualBody>& VirtualBodies, TArray<FVector>& DrawPoints) const;
	void UpdateVelocities(TArray<FVirtualBody>& VirtualBodies) const;
	void UpdatePositions(TArray<FVirtualBody>& VirtualBodies, TArray<FVector>& DrawPoints, const int& Step) const;
	void DrawPaths(const TArray<FVirtualBody>& VirtualBodies, const TArray<FVector>& DrawPoints, TArray<AActor*> Bodies) const;
	FVector CalculateAcceleration(const int& BodyIndex, const TArray<FVirtualBody>& VirtualBodies) const;
};
