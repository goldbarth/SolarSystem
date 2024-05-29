// Copyright Epic Games, Inc. All Rights Reserved.


#include "OrbitDebugDisplay.h"

#include "OrbitDebugDisplayCommands.h"
#include "OrbitDebugDisplayStyle.h"
#include "ToolMenus.h"
#include "Framework/Notifications/NotificationManager.h"
#include "SolarSystem/Defines/Debug.h"
#include "OrbitDebugDisplay/DisplayStyle.h"
#include "OrbitDebugDisplay/DisplayText.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Widgets/Text/STextBlock.h"

static const FName OrbitDebugDisplayTabName("OrbitDebugDisplay");

#define LOCTEXT_NAMESPACE "FOrbitDebugDisplayModule"

void FOrbitDebugDisplayModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FOrbitDebugDisplayStyle::Initialize();
	FOrbitDebugDisplayStyle::ReloadTextures();

	FOrbitDebugDisplayCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FOrbitDebugDisplayCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FOrbitDebugDisplayModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FOrbitDebugDisplayModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(OrbitDebugDisplayTabName, FOnSpawnTab::CreateRaw(this, &FOrbitDebugDisplayModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FOrbitDebugDisplayTabTitle", "OrbitDebugDisplay"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FOrbitDebugDisplayModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FOrbitDebugDisplayStyle::Shutdown();

	FOrbitDebugDisplayCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(OrbitDebugDisplayTabName);
}

TSharedRef<SDockTab> FOrbitDebugDisplayModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
#pragma region MainVerticalBox
	
	const TSharedRef<SVerticalBox> MainVerticalBox = SNew(SVerticalBox);

	MainVerticalBox->AddSlot()
		.AutoHeight()
		.Padding(DisplayStyle::LargePadding)
		[
			SNew(STextBlock)
			.Text(DisplayText::HeaderText)
			.TextStyle(&DisplayStyle::TextStyle)
		];

	AddCheckboxRow(DisplayText::DrawDebugPathsLabel, DisplayText::DrawDebugPathsTooltip, DebugPaths,
	               FOnCheckStateChanged::CreateRaw(this, &FOrbitDebugDisplayModule::HandleDrawDebugPathsCheckBoxStateChanged), MainVerticalBox);

	AddCheckboxRow(DisplayText::DrawSplinePathsLabel, DisplayText::DrawSplinePathsTooltip, SplinePaths,
		FOnCheckStateChanged::CreateRaw(this, &FOrbitDebugDisplayModule::HandleDrawSplinePathsCheckBoxStateChanged), MainVerticalBox);
	
	AddTextBoxRow(DisplayText::LineThicknessLabel, DisplayText::DefaultLineThickness, DisplayText::LineThicknessTooltip,
	              FOnTextCommitted::CreateRaw(this, &FOrbitDebugDisplayModule::HandleLineThicknessTextCommited), MainVerticalBox);
	
	AddTextBoxRow(DisplayText::NumStepsLabel, DisplayText::DefaultNumSteps, DisplayText::NumStepsTooltip,
	              FOnTextCommitted::CreateRaw(this, &FOrbitDebugDisplayModule::HandleNumStepsTextCommited), MainVerticalBox);
	
	AddTextBoxRow(DisplayText::TimeStepLabel, DisplayText::DefaultTimeStep, DisplayText::TimeStepTooltip,
	              FOnTextCommitted::CreateRaw(this, &FOrbitDebugDisplayModule::HandleTimeStepTextCommited), MainVerticalBox);
	
	return SNew(SDockTab)
		.TabRole(NomadTab)
		.OnTabClosed(SDockTab::FOnTabClosedCallback::CreateLambda([this](TSharedRef<SDockTab>)
			{
				DestroyOrbitDebugActor();
			}))
		[
			MainVerticalBox
		];
}

#pragma endregion

#pragma region OrbitDebugDisplayActions

ECheckBoxState FOrbitDebugDisplayModule::IsDrawBoxChecked(const EDrawPathType PathType) const
{
	return (CurrentPathType == PathType && CurrentPathType != None) ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
}

void FOrbitDebugDisplayModule::HandleDrawDebugPathsCheckBoxStateChanged(const ECheckBoxState NewState)
{
	HandleCheckBoxStateChanged(NewState, DebugPaths, DrawDebugPaths);    
}

void FOrbitDebugDisplayModule::HandleDrawSplinePathsCheckBoxStateChanged(const ECheckBoxState NewState)
{
	HandleCheckBoxStateChanged(NewState, SplinePaths, DrawSplinePaths);
}

void FOrbitDebugDisplayModule::HandleLineThicknessTextCommited(const FText& Text, const ETextCommit::Type CommitType)
{
	HandleTextBoxChanged(Text, CommitType, LineThickness);
}

void FOrbitDebugDisplayModule::HandleNumStepsTextCommited(const FText& Text, const ETextCommit::Type CommitType)
{
	HandleTextBoxChanged(Text, CommitType, NumSteps);
}

void FOrbitDebugDisplayModule::HandleTimeStepTextCommited(const FText& Text, const ETextCommit::Type CommitType)
{
	HandleTextBoxChanged(Text, CommitType, TimeStep);
}

#pragma endregion

#pragma region Widget Row Templates

template <typename FuncType>
void FOrbitDebugDisplayModule::AddCheckboxRow(const FText& LabelText, const FText& TooltipText, const EDrawPathType& PathType,
	FuncType OnCheckStateChanged, const TSharedRef<SVerticalBox> ParentBox)
{
	const TSharedRef<SVerticalBox> VerticalBox = SNew(SVerticalBox);

	VerticalBox->AddSlot()
		.AutoHeight()
		.Padding(DisplayStyle::MediumPadding)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				CreateTextBlock({LabelText, TooltipText})
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				CreateCheckBox({LabelText, TooltipText, PathType, OnCheckStateChanged})
			]
		];

	ParentBox->AddSlot()
		.AutoHeight()
		.Padding(DisplayStyle::MidSmallPadding)
		[
			VerticalBox
		];
}

template <typename FuncType>
void FOrbitDebugDisplayModule::AddTextBoxRow(const FText& LabelText, const FText& DefaultTextBoxText, const FText& TooltipText,
	FuncType OnTextCommited, const TSharedRef<SVerticalBox> ParentBox)
{
	const TSharedRef<SVerticalBox> VerticalBox = SNew(SVerticalBox);

	VerticalBox->AddSlot()
		.AutoHeight()
		.Padding(DisplayStyle::SmallPadding)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				CreateTextBlock({LabelText, TooltipText})
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				CreateTextBox({LabelText, DefaultTextBoxText, TooltipText, OnTextCommited})
			]
		];

	ParentBox->AddSlot()
		.AutoHeight()
		.Padding(DisplayStyle::SmallPadding)
		[
			VerticalBox
		];
}

TSharedRef<SWidget> FOrbitDebugDisplayModule::CreateCheckBox(const FCheckboxRowParams& Params) const
{
	return SNew(SCheckBox)
		.IsChecked_Lambda([this, Params]() 
		{
			return IsDrawBoxChecked(Params.PathType);
		})
		.OnCheckStateChanged(Params.OnCheckStateChanged)
		.ToolTipText(Params.Tooltip);
}

TSharedRef<SWidget> FOrbitDebugDisplayModule::CreateTextBox(const FTextBoxRowParams& Params)
{
	return SNew(SEditableTextBox)
		.Text(Params.DefaultTextBoxText)
		.OnTextCommitted(Params.OnTextCommited)
		.ToolTipText(Params.Tooltip);
}

TSharedRef<SWidget> FOrbitDebugDisplayModule::CreateTextBlock(const FTextBlockParams& Params)
{
	return SNew(STextBlock)
		.Text(Params.Label)
		.ToolTipText(Params.Tooltip);
}

#pragma endregion

#pragma region OrbitDebugDisplayActions

void FOrbitDebugDisplayModule::TrySpawnOrbitDebugActor()
{
	if (OrbitDebugger != nullptr) return;
	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (World != nullptr)
	{
		OrbitDebugger = World->SpawnActor<AOrbitDebug>(AOrbitDebug::StaticClass());
	}
	else
	{
		LOG_DISPLAY("Debug Actor could not be spawned. World is nullptr.");
	}
}

void FOrbitDebugDisplayModule::DestroyOrbitDebugActor()
{
	CurrentPathType = None;
	if (OrbitDebugger == nullptr) return;
	OrbitDebugger->Destroy();
	OrbitDebugger = nullptr;
}

void FOrbitDebugDisplayModule::HandleCheckBoxStateChanged(const ECheckBoxState NewState, const EDrawPathType PathType, const EDebugMode DebugMode)
{
	TrySpawnOrbitDebugActor();
	if (NewState == ECheckBoxState::Checked)
	{
		CurrentPathType = PathType;
        
		switch (PathType)
		{
		case DebugPaths:
			OrbitDebugger->SetDrawOrbitPaths(true);
			OrbitDebugger->SetDrawSplines(false);
			break;
		case SplinePaths:
			OrbitDebugger->SetDrawOrbitPaths(false);
			OrbitDebugger->SetDrawSplines(true);
			break;
		default:
			LOG_WARNING_F("No valid path type found for %hs in %hs", __FUNCTION__, __FILE__);
			break;
		}
	}
	else
	{
		CurrentPathType = None;
		OrbitDebugger->SetDrawOrbitPaths(false);
		OrbitDebugger->SetDrawSplines(false);
	}
}

void FOrbitDebugDisplayModule::HandleTextBoxChanged(const FText& Text, const ETextCommit::Type CommitType, const ETextCommitType Type)
{
	if (CommitType == ETextCommit::OnEnter)
	{
		const FString TextString = Text.ToString();
		if (TextString.IsNumeric())
		{
			const float Value = FCString::Atof(*Text.ToString());
			SetTextValue(Value, Type);
		}
		else
		{
			DrawInvalidPromptNotification();
		}
	}
}

void FOrbitDebugDisplayModule::SetTextValue(const float Value, const ETextCommitType Type)
{
	switch (Type)
	{
	case LineThickness:
		SetLineThickness(Value);
		break;
	case TimeStep:
		SetTimeStep(Value);
		break;
	case NumSteps:
		SetNumSteps(Value);
		break;
	}
}

void FOrbitDebugDisplayModule::SetLineThickness(const float LineThickness)
{
	TrySpawnOrbitDebugActor();
	OrbitDebugger->SetLineThickness(LineThickness);
}

void FOrbitDebugDisplayModule::SetNumSteps(const int NumSteps)
{
	TrySpawnOrbitDebugActor();
	OrbitDebugger->SetNumSteps(NumSteps);
}

void FOrbitDebugDisplayModule::SetTimeStep(const float TimeSteps)
{
	TrySpawnOrbitDebugActor();
	OrbitDebugger->SetTimeStep(TimeSteps);
}

void FOrbitDebugDisplayModule::DrawInvalidPromptNotification()
{
	const FText NotificationText = FText::FromString(TEXT("Please enter a valid number."));
	FNotificationInfo Info(NotificationText);
	Info.bFireAndForget = true;
	Info.FadeOutDuration = 1.0f;
	Info.ExpireDuration = 2.0f;
	FSlateNotificationManager::Get().AddNotification(Info);
}

#pragma endregion


void FOrbitDebugDisplayModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(OrbitDebugDisplayTabName);
}

void FOrbitDebugDisplayModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FOrbitDebugDisplayCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FOrbitDebugDisplayCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FOrbitDebugDisplayModule, OrbitDebugDisplay)