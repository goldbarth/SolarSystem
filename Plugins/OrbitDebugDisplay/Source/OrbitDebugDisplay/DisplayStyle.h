#pragma once

namespace DisplayStyle
{
	constexpr int LargePadding =	20;
	constexpr int MediumPadding =	10;
	constexpr int MidSmallPadding =	7;
	constexpr int SmallPadding =	5;
	
	constexpr int FontSize = 9;
	
	constexpr FLinearColor LightGrey = FLinearColor(0.3f, 0.3f, 0.3f, 1.0f);
	
	const FTextBlockStyle TextStyle = FTextBlockStyle(FCoreStyle::Get()
												.GetWidgetStyle<FTextBlockStyle>("NormalText"))
												.SetColorAndOpacity(LightGrey)
												.SetFontSize(FontSize);
};
