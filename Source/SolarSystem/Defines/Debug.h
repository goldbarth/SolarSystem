// Copyright (c) 2024 Felix Wahl (https://github.com/goldbarth). Provided under the MIT License. Full text: https://opensource.org/licenses/MIT

#pragma once

// Debugging macros

#define LOG_DISPLAY(Format, ...) UE_LOG(LogTemp, Display, TEXT(Format), ##__VA_ARGS__)
#define LOG_WARNING(Format, ...) UE_LOG(LogTemp, Warning, TEXT(Format), ##__VA_ARGS__)
#define LOG_ERROR(Format, ...) UE_LOG(LogTemp, Error, TEXT(Format), ##__VA_ARGS__)

#define LOG_DISPLAY_F(Format, ...) UE_LOG(LogTemp, Display, TEXT("%s: %s"), *FString(__FUNCTION__), *FString::Printf(TEXT(Format), ##__VA_ARGS__))
#define LOG_WARNING_F(Format, ...) UE_LOG(LogTemp, Warning, TEXT("%s: %s"), *FString(__FUNCTION__), *FString::Printf(TEXT(Format), ##__VA_ARGS__))
#define LOG_ERROR_F(Format, ...) UE_LOG(LogTemp, Error, TEXT("%s: %s"), *FString(__FUNCTION__), *FString::Printf(TEXT(Format), ##__VA_ARGS__))

#define PRINT_DISPLAY(Engine, Time, Format, ...) if (Engine) { Engine->AddOnScreenDebugMessage(-1, Time, FColor::Green, FString::Printf(TEXT(Format), ##__VA_ARGS__)); }
#define PRINT_WARNING(Engine, Time, Format, ...) if (Engine) { Engine->AddOnScreenDebugMessage(-1, Time, FColor::Yellow, FString::Printf(TEXT(Format), ##__VA_ARGS__)); }
#define PRINT_ERROR(Engine, Time, Format, ...) if (Engine) { Engine->AddOnScreenDebugMessage(-1, Time, FColor::Red, FString::Printf(TEXT(Format), ##__VA_ARGS__)); }

#define PRINT_DISPLAY_F(Engine, Time, Format, ...) if (Engine) { Engine->AddOnScreenDebugMessage(-1, Time, FColor::Green, FString::Printf(TEXT("%s: %s"), *FString(__FUNCTION__), *FString::Printf(TEXT(Format), ##__VA_ARGS__))); }
#define PRINT_WARNING_F(Engine, Time, Format, ...) if (Engine) { Engine->AddOnScreenDebugMessage(-1, Time, FColor::Yellow, FString::Printf(TEXT("%s: %s"), *FString(__FUNCTION__), *FString::Printf(TEXT(Format), ##__VA_ARGS__))); }
#define PRINT_ERROR_F(Engine, Time, Format, ...) if (Engine) { Engine->AddOnScreenDebugMessage(-1, Time, FColor::Red, FString::Printf(TEXT("%s: %s"), *FString(__FUNCTION__), *FString::Printf(TEXT(Format), ##__VA_ARGS__))); }