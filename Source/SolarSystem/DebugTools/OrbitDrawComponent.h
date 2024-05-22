// Copyright (c) 2024 Felix Wahl (https://github.com/goldbarth). Provided under the MIT License. Full text: https://opensource.org/licenses/MIT

#pragma once

#include "CoreMinimal.h"
#include "IVirtualBody.h"
#include "Components/ActorComponent.h"
#include "OrbitDrawComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SOLARSYSTEM_API UOrbitDrawComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UOrbitDrawComponent();

private:
	IVirtualBody* OrbitDrawer = nullptr;
	
	void DrawOrbits() const;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
								FActorComponentTickFunction* ThisTickFunction) override;
};
