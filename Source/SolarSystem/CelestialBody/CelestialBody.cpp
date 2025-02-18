// Author (c) 2024 Felix Wahl (https://github.com/goldbarth). Provided under the MIT License. Full text: https://opensource.org/licenses/MIT

#include "CelestialBody.h"

#include "SolarSystem/GameModes/OrbitSimulation_GameMode.h"
#include "SolarSystem/Orbit/ACelestialBodyRegistry.h"
#include "SolarSystem/Structs/Universe.h"
#include "../Defines/Debug.h"


ACelestialBody::ACelestialBody()
{
	PrimaryActorTick.bCanEverTick = true;
	SetMeshComponent();
}

void ACelestialBody::BeginPlay()
{
	Super::BeginPlay();
	SetCurrentVelocity(InitialVelocity);
	SetRadius();
	MassCalculation();
	
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ACelestialBody::AddBodyToRegistry, 0.5f, false);
}

void ACelestialBody::SetMeshComponent()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetEnableGravity(false);
}

void ACelestialBody::SetMass(const float& NewMass)
{
	Mass = NewMass;
	MeshComponent->SetMassOverrideInKg(NAME_None, Mass, true);
}

void ACelestialBody::UpdateVelocity(const FVector& Acceleration, const float& TimeStep)
{
	CurrentVelocity += Acceleration * TimeStep;
}

void ACelestialBody::UpdatePosition(const float& TimeStep) const
{
	MeshComponent->SetPhysicsLinearVelocity(CurrentVelocity * TimeStep);
}

void ACelestialBody::MassCalculation()
{
	Mass = Radius * Radius / FUniverse::GravitationalConstant;
	MeshComponent->SetMassOverrideInKg(NAME_None, Mass, true);
}

void ACelestialBody::AddBodyToRegistry()
{
	AOrbitSimulation_GameMode* GameMode = Cast<AOrbitSimulation_GameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		ACelestialBodyRegistry* Registry = GameMode->GetCelestialBodyRegistry();
		if (Registry)
		{
			Registry->OnCelestialBodyAdded.Broadcast(this);
		}
		else
		{
			LOG_ERROR_F("Failed to get CelestialObjectManager from Game Mode! @ %s", *GetName());
		}
	}
	else
	{
		LOG_ERROR_F("Failed to cast Game Mode! @ %s", *GetName());
	}
}

