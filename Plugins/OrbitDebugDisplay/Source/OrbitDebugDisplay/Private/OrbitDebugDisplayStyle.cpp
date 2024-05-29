// Copyright Epic Games, Inc. All Rights Reserved.

#include "OrbitDebugDisplayStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FOrbitDebugDisplayStyle::StyleInstance = nullptr;

void FOrbitDebugDisplayStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FOrbitDebugDisplayStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FOrbitDebugDisplayStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("OrbitDebugDisplayStyle"));
	return StyleSetName;
}

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FOrbitDebugDisplayStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("OrbitDebugDisplayStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("OrbitDebugDisplay")->GetBaseDir() / TEXT("Resources"));

	Style->Set("OrbitDebugDisplay.OpenPluginWindow", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));

	return Style;
}

void FOrbitDebugDisplayStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FOrbitDebugDisplayStyle::Get()
{
	return *StyleInstance;
}
