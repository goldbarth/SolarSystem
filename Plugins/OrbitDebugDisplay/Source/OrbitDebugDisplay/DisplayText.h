#pragma once

#define LOCTEXT_NAMESPACE "DisplayText"

namespace DisplayText
{
	const FText HeaderText = LOCTEXT("OrbitDebugDisplayTabTitle", "Orbit Debugger");
	
	const FText DrawDebugPathsLabel = LOCTEXT("DrawDebugPathsLabel", "Draw Debug Paths: ");
	const FText DrawSplinePathsLabel = LOCTEXT("DrawSlinePathsLabel", "Draw Spline Paths: ");
	const FText LineThicknessLabel = LOCTEXT("LineThicknessLabel", "   Line Thickness: ");
	const FText NumStepsLabel = LOCTEXT("NumStepsLabel", "   Number of Steps: ");
	const FText TimeStepLabel = LOCTEXT("TimeStepLabel", "   Number of Time Steps: ");

	const FText DrawDebugPathsTooltip = LOCTEXT("DrawDebugPathsTooltip", "Activate this option to draw orbits for all celestial bodies.");
	const FText DrawSplinePathsTooltip = LOCTEXT("DrawSplinePathsTooltip", "Activate this option to draw spline orbits, deactivating the default orbit paths.");
	const FText LineThicknessTooltip = LOCTEXT("LineThicknessTooltip", "Enter a line thickness for the orbits. A range of 0.1-10.0 is recommended.");
	const FText NumStepsTooltip = LOCTEXT("NumStepsTooltip", "Enter a number of steps to draw the orbits. A range of 100-500 is recommended.");
	const FText TimeStepTooltip = LOCTEXT("TimeStepTooltip", "Enter a time step to draw the orbits. A range of 100.0-1000.0 is recommended. With higher numbers, the paths are calculated further ahead.");

	const FText DefaultLineThickness = LOCTEXT("DefaultLineThickness", "1.0");
	const FText DefaultNumSteps = LOCTEXT("DefaultNumSteps", "100");
	const FText DefaultTimeStep = LOCTEXT("DefaultTimeStep", "500.0");
};

#undef LOCTEXT_NAMESPACE
