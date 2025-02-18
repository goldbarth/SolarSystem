// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "SolarSystem/DebugTools/OrbitDebug.h"

enum EDebugMode
{
	DrawDebugPaths,
	DrawSplinePaths
};

enum EDrawPathType
{
	None,
	DebugPaths,
	SplinePaths
};

enum ETextCommitType
{
	LineThickness,
	TimeStep,
	NumSteps
};

struct FCheckboxRowParams
{
	FText Label;
	FText Tooltip;
	EDrawPathType PathType;
	FOnCheckStateChanged OnCheckStateChanged;
};

struct FTextBoxRowParams
{
	FText Label;
	FText DefaultTextBoxText;
	FText Tooltip;
	FOnTextCommitted OnTextCommited;
};

struct FTextBlockParams
{
	FText Label;
	FText Tooltip;
};

class FToolBarBuilder;
class FMenuBuilder;

/**
 * The public interface to this module to be used to create a debug window for the OrbitDebug class
 */
class FOrbitDebugDisplayModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();

private:

	void RegisterMenus();

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);
	ECheckBoxState IsDrawBoxChecked(EDrawPathType PathType) const;

#pragma region Custom Widget Creation

	TSharedRef<SWidget> CreateCheckBox(const FCheckboxRowParams& Params) const;
	TSharedRef<SWidget> CreateTextBox(const FTextBoxRowParams& Params);
	TSharedRef<SWidget> CreateTextBlock(const FTextBlockParams& Params);
	
	void HandleDrawDebugPathsCheckBoxStateChanged(ECheckBoxState NewState);
	void HandleDrawSplinePathsCheckBoxStateChanged(ECheckBoxState NewState);
	void HandleLineThicknessTextCommited(const FText& Text, ETextCommit::Type CommitType);
	void HandleNumStepsTextCommited(const FText& Text, ETextCommit::Type CommitType);
	void HandleTimeStepTextCommited(const FText& Text, ETextCommit::Type CommitType);

#pragma endregion

#pragma region Widget Row Templates

	template<typename FuncType>
	void AddCheckboxRow(const FText& LabelText, const FText& TooltipText, const EDrawPathType& PathType, FuncType OnCheckStateChanged, const TSharedRef<SVerticalBox> ParentBox);
	
	template<typename FuncType>
	void AddTextBoxRow(const FText& LabelText, const FText& DefaultTextBoxText, const FText& TooltipText, FuncType OnTextCommited, const TSharedRef<SVerticalBox> ParentBox);

#pragma endregion

#pragma region OrbitDebugActions and Variables
	
	AOrbitDebug* OrbitDebugger = nullptr;
	
	EDrawPathType CurrentPathType = None;

	void TrySpawnOrbitDebugActor();
	void DestroyOrbitDebugActor();
	
	void HandleCheckBoxStateChanged(const ECheckBoxState NewState, const EDrawPathType PathType, const EDebugMode DebugMode);
	void HandleTextBoxChanged(const FText& Text, const ETextCommit::Type CommitType, const ETextCommitType Type);
	void SetTextValue(float Value, ETextCommitType Type);
	void SetLineThickness(const float LineThickness);
	void SetTimeStep(const float TimeSteps);
	void SetNumSteps(const int NumSteps);
	
	void DrawInvalidPromptNotification();

#pragma endregion

	TSharedPtr<class FUICommandList> PluginCommands;
};


