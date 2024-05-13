# Solar System Simulation (Unreal Engine 5.3.2)

An interactive solar system project in Unreal Engine, designed as a hands-on to C++, game physics, and engine fundamentals.
This repository serves as a platform to gain deep insights into Unreal Engine programming through the development of an orbital simulation project,
exploring both basic and advanced concepts of game development.

Disclaimer: The project is a work in progress and may be subject to changes and updates.

## Table of Contents

- [Features](#features)
- [Introduction](#introduction)
- [Getting Started](#getting-started)
  - [Implement basic classes](#implement-basic-classes) 
    - [CelestialBody class](#celestialbody-class)
      - [Properties](#celestialbody-properties)
      - [Mesh Initialization](#mesh-initialization)
      - [Getter and setter functions](#getter-and-setter-functions)
      - [Physics functions](#physics-functions)
      - [Gravitational constant / Universe struct](#gravitational-constant)
    - [CelestialBodyRegistry class](#celestialbodyregistry-class)
      - [Delegate](#celestialbodyregistry-delegate)
      - [Properties](#celestialbodyregistry-properties)
      - [Functions](#celestialbodyregistry-functions)
    - [Game-Mode class](#game-mode-class)
      - [Expanding the CelestialBody class](#expanding-the-celestialbody-class)
    - [OrbitSimulation class](#orbitsimulation-class)
      - [Properties](#orbitsimulation-properties)
      - [Functions](#orbitsimulation-functions)
      - [Expanding the game-mode class](#expanding-the-game-mode-class)
    - [Creating the Simulation](#creating-the-simulation)
      - [Creating the level](#creating-the-level)
      - [Adding the game-mode](#adding-the-game-mode)
      - [Adding the celestial bodies](#adding-the-celestial-bodies)
        - [Creating the base blueprint](#creating-the-base-blueprint)
        - [Creating the base material](#creating-the-base-material)
- [Resources](#resources)

<a name="introduction"></a>
## Introduction

The project enables hands-on learning of Unreal Engine's core elements such as the gameplay framework, physics, user interfaces, and input handling. 
By implementing a planetary simulation, programmers can improve their C++ skills and develop an understanding of the architecture and functionality of a game engine.

The step-by-step guide leads from the basics, like setting up a project and creating C++ classes, to advanced topics such as physics calculations and procedural generation. 
Best practices and conventions for programming with the Unreal Engine are conveyed throughout the process.

The goal is to gain a deep understanding of Unreal development through a concrete project, which can also be transferred to other areas of application. 
The repository is intended to serve as a reference and starting point for own experiments and extensions.

Basic C++ knowledge, understanding of game development, and the Unreal Engines are necessary and required.

<a name="features"></a>
## Features

- Implementation of an interactive solar system simulation
- Use of C++ for programming
- Application of physics and mathematics for the simulation of celestial bodies
- Tool for visualizing orbits and planets
- Customization options for the simulation
- Integration of user interfaces and input handling
- Performance optimization through e.g., task graphs and multithreading, allocator optimization, and burst compiler

Note: The simulation can be extended by implementing additional functions and mechanics to personalize and enhance the project. 
For example, it may be expanded with a spacecraft and further physics to create an immersive experience. 
Much can still change in development and will be documented.

<a name="getting-started"></a>
## Getting Started

##### Creating a New Project in Unreal Engine 5.3.2

1. Launch Unreal Engine and select "Blank" under Games as the project template and C++ as the project defaults.
2. Choose a location for the project, select a name, and click "Create Project"

##### Creating a New C++ Class

1. In the engine, click on "Tools" → "New C++ Class"
2. Choose a class derived from a base class, e.g., `AActor` or `None` for an empty class, useful for utility classes.
3. Choose Public or Private for the access level and select a name for the class.
4. Click "Create Class" to create the class.
5. Click "Yes" to regenerate the project files.
6. Click "Compile" to compile the class.

Note 1: It is possible to create a new class in the IDE and add it to the project manually.
It is also a good idea to create a clear folder structure to organize the classes.
The classes must be stored in a suitable folder, e.g. `MyGame/Games/MyGame/Source/MyGameClasses` or `MyGame/Source/MyGameClasses`.

Note 2: The engine automatically generates the header and source files for the new class and adds them to the project.
Compiling the class creates the binary files and makes the class available in the editor. In Unreal, it is important to recompile the class after each change.

<a name="implement-basic-classes"></a>
##### Implement Basic Classes

###### CelestialBody Class

First, we create the class that will serve as the basis for all celestial bodies in the solar system.
To do this, we create a new C++ class derived from `AActor` and add the necessary properties and functions.

The header should look like this:

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CelestialBody.generated.h"

UCLASS()
class SOLARSYSTEM_API ACelestialBody : public AActor
{
	GENERATED_BODY()

public:
	ACelestialBody();

protected:
	virtual void BeginPlay() override;
};
```

We will deal with the source file `CelestialBody.cpp` later.


<a name="celestialbody-properties"></a>
###### *CelestialBody Properties:*

For now, let's add the properties to define the celestial bodies.

We need the following properties:
- mass
- radius
- initial velocity
- current velocity and
- line color for the orbit visualization 

The properties for the celestial bodies should look like this:

```cpp
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Celestial Body")
	float Mass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Celestial Body")
	float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Celestial Body")
	FVector InitialVelocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Celestial Body")
	FVector CurrentVelocity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug Options")
	mutable FLinearColor LineColor;
```

The mass, radius and initial velocity are editable in the blueprint so that we can configure the celestial bodies in the editor.
The current velocity is read-only, as it changes during the simulation.
The line color is editable in the blueprint to visualize the orbits of the celestial bodies.
It is also mutable so that it can be changed in a const function.

We also need a mesh component to make the celestial body visible in the editor and to enable the physics simulation,
in which we set the mesh components mass and get the radius of the component.

The properties for the mesh component should look like this:

```cpp
protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Celestial Body")
    UStaticMeshComponent* MeshComponent;
```


<a name="mesh-initialization"></a>
###### *Mesh Initialization:*

The mesh component is initialized in the constructor.

The constructor implementation should look like this in the source file `CelestialBody.cpp`:

```cpp
#include "CelestialBody.h"


ACelestialBody::ACelestialBody()
{
        PrimaryActorTick.bCanEverTick = true;

        MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetEnableGravity(false);
}
```
The constructor initializes the mesh component and sets the physics simulation and gravity settings.
We set the physics simulation to `true` so that the component performs physics simulations.
We set the gravity settings to `false` because we will implement our own gravity simulation.


<a name="getter-and-setter-functions"></a>
###### *Getter and setter functions:*

To access and change the properties of the celestial bodies, we create getter and setter functions.

The getter and setter functions should look like this:

```cpp
public:
	float GetMass() const { return Mass; }
	void SetMass(const float& NewMass);

	float GetRadius() const { return Radius; }
	void SetRadius() { Radius = MeshComponent->Bounds.SphereRadius; }

	FVector GetInitialVelocity() const { return InitialVelocity; }
	void SetCurrentVelocity(const FVector& NewVelocity) { CurrentVelocity = NewVelocity; }
```

Except for the `SetMass` function, all functions are defined inline, as they only perform a simple return or assignment.
The function `SetRadius` sets the radius of the celestial body to the radius of the mesh component
to determine the size of the celestial body,
which is defined by the size of the mesh component.

The function `SetMass` should look like this in the source file `CelestialBody.cpp`:

```cpp
void ACelestialBody::SetMass(const float& NewMass)
{
	Mass = NewMass;
	MeshComponent->SetMassOverrideInKg(NAME_None, Mass, true);
}
```

The function `SetMass` sets the mass of the celestial body and overwrites the mass of the mesh component to set the mass of the celestial body.


<a name="physics-functions"></a>
###### *Physics functions:*

To implement the physics simulation, we create functions that calculate the gravitational simulation and the motion of the celestial bodies.

The functions should look like this in the header file `CelestialBody.h`:

```cpp
public:
	void UpdatePosition(const float& TimeStep) const;
	void UpdateVelocity(const FVector& Acceleration, const float& TimeStep);
	
private:
	void MassCalculation();
```

The implementation of the functions should look like this in the source file `CelestialBody.cpp`:

```cpp
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
```

The function `UpdateVelocity` calculates the velocity of the celestial body based on the acceleration and the time interval.

The `UpdatePosition` function updates the position of the celestial body based on the current velocity and the time interval.
The velocity is multiplied by the time interval to update the position of the celestial body and control the movement via the mesh component.

The function `MassCalculation` calculates the mass of the celestial body based on the `Radius` and the gravitational constant<sup>*</sup> `G`.
The formula for the mass calculation is
`m = r² * G` or `Mass = Radius * Radius * G`.
The result is saved in the mass property, and the mass of the mesh component is overwritten.

------------------------------------------------------------------------------------------------------------

<a name="gravitational-constant"></a>
##### Gravitational Constant

<sup>*</sup> We define the gravitational constant `G` and the structure `FUniverse` in the newly created header file `Universe.h`.

The header file `Universe.h` should look like this:

```cpp
#pragma once

#include "CoreMinimal.h"

struct FUniverse
{
	static constexpr float GravitationalConstant = 0.1f; // 6.67430e-11f | m^3 kg^-1 s^-2
};
```

The gravitational constant is defined as `constexpr` in order to calculate it at compile time and use it as a constant.

The gravitational constant is defined as `0.1f` to simplify the simulation and to scale the values.

For the simulation, we use a fixed time step size of `0.1f` to control the simulation and calculate the orbits.

------------------------------------------------------------------------------------------------------------

<a name="celestialbodyregistry-class"></a>
##### CelestialBodyRegistry Class

Next, we create the class that registers and manages the celestial bodies to use them in the simulation.
To do this, we create a new C++ class derived from `AActor` and add the necessary properties and functions.

The header file `CelestialBodyRegistry.h` should look like this:

```cpp
#pragma once

#include “CoreMinimal.h”
#include “GameFramework/Actor.h”
#include “ACelestialBodyRegistry.generated.h”

UCLASS()
class SOLARSYSTEM_API ACelestialBodyRegistry : public AActor
{
	GENERATED_BODY()

public:
	ACelestialBodyRegistry();
};
```

<a name="celestialbodyregistry-delegate"></a>
###### *CelestialBodyRegistry Delegate:*

The delegate `FCelestialObjectAddedDelegate` is defined to enable the addition of celestial objects.

The delegate should look like this in the header file `CelestialBodyRegistry.h`:

```cpp
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCelestialObjectAddedDelegate, ACelestialBody*, CelestialObject);

UCLASS()
class SOLARSYSTEM_API ACelestialBodyRegistry : public AActor
{
	GENERATED_BODY()

public:
	ACelestialBodyRegistry();
	
	UPROPERTY(BlueprintAssignable)
	FCelestialObjectAddedDelegate OnCelestialBodyAdded;
};
```

The implementation of the delegate should look like this in the source file or constructor `CelestialBodyRegistry.cpp`:

```cpp
#include “ACelestialBodyRegistry.h”


ACelestialBodyRegistry::ACelestialBodyRegistry()
{
	OnCelestialBodyAdded.AddDynamic(this, &ACelestialBodyRegistry::AddCelestialObject);
}
```

The delegate `OnCelestialBodyAdded` is accessible in the blueprint
and is initialized in the constructor to enable the addition of celestial bodies.
We can use the delegate to register and manage celestial bodies in another class.

<a name="celestialbodyregistry-properties"></a>
###### *CelestialBodyRegistry Properties:*

Now we add the properties to register the celestial bodies.

- Delegates for adding celestial bodies (see above)
- Array for the celestial bodies

The properties for the celestial body registry should look like this:

```cpp
public:
	ACelestialBodyRegistry();

	UPROPERTY(BlueprintAssignable)
	FCelestialObjectAddedDelegate OnCelestialBodyAdded;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = “Celestial Objects”)
	TArray<ACelestialBody*> CelestialBodies;
```

The array `CelestialBodies` is read-only and contains all registered celestial bodies.

So that we can use the ACelestialBody pointers, we must include the `CelestialBody.h`.

The include directive should look like this in the source file
`CelestialBodyRegistry.h` (possibly with folder structure):

```cpp
#include “CoreMinimal.h”
#include “GameFramework/Actor.h”
#include “CelestialBody.h”
#include “ACelestialBodyRegistry.generated.h”
```

<a name="celestialbodyregistry-functions"></a>
###### *CelestialBodyRegistry Functions:*

Now we add the functions to register and manage the celestial bodies.

The functions should look like this:

```cpp
public:
	UFUNCTION()
	void AddCelestialObject(ACelestialBody* CelestialObject);
	
	void RemoveCelestialObject(ACelestialBody* CelestialObject);
	
	TArray<ACelestialBody*> GetCelestialObjects() const { return CelestialBodies; }
```

The getter function `GetCelestialObjects` is `inline`
and returns the array of celestial bodies so that we can access the celestial bodies.

The implementation of the other functions should look like this in the source file `CelestialBodyRegistry.cpp`:

```cpp
#include “ACelestialBodyRegistry.h”


ACelestialBodyRegistry::ACelestialBodyRegistry()
{
	OnCelestialBodyAdded.AddDynamic(this, &ACelestialBodyRegistry::AddCelestialObject);
}

void ACelestialBodyRegistry::AddCelestialObject(ACelestialBody* CelestialObject)
{
	if (CelestialObject && !CelestialBodies.Contains(CelestialObject))
	{
		CelestialBodies.Add(CelestialObject);
	}
}

void ACelestialBodyRegistry::RemoveCelestialObject(ACelestialBody* CelestialObject)
{
	if (CelestialBodies.Contains(CelestialObject))
	{
		CelestialBodies.Remove(CelestialObject);
	}
}
```

In the function `AddCelestialObject` the celestial body is added
if it is not `nullptr` and is not yet contained in the array.

In the `RemoveCelestialObject` function, the celestial object is removed if it is contained in the array.

------------------------------------------------------------------------------------------------------------

<a name="game-mode-class"></a>
##### Game-Mode Class

To extend the classes,
we must first create a GameMode class in which we control the simulation and register and manage the celestial bodies.
In the GameMode class,
we initialize the simulation and add the celestial bodies to calculate the orbits and control the simulation.

To do this, we create a new C++ class derived from `AGameModeBase` and add the necessary properties and functions.

The header file `OrbitSimulation_GameMode.h` should look like this:

```cpp
#pragma once

#include “CoreMinimal.h”
#include “GameFramework/GameModeBase.h”
#include “ACelestialBodyRegistry.h”
#include “OrbitSimulation_GameMode.generated.h”

/**
 * 
 */
UCLASS()
class SOLARSYSTEM_API ADemoOrbitSimulation_GameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = “Celestial Objects”)
	ACelestialBodyRegistry* CelestialBodyRegistry;


public:
	virtual void StartPlay() override;
	
	ACelestialBodyRegistry* GetCelestialBodyRegistry() const { return CelestialBodyRegistry; }

	
private:
	void Initialize();
	
};
```

We have added the `CelestialBodyRegistry` property,
an `inline` getter function for the registry and the `Initialize` function to initialize the simulation.

The implementation of the function should look like this in the source file `OrbitSimulation_GameMode.cpp`:

```cpp
#include “OrbitSimulation_GameMode.h”


void AOrbitSimulation_GameMode::StartPlay()
{
	Super::StartPlay();
	
	Initialize();
}

void AOrbitSimulation_GameMode::Initialize()
{
	UWorld* World = GetWorld();
	if (World)
	{
		CelestialBodyRegistry = World->SpawnActor<ACelestialBodyRegistry>();
		if (!CelestialBodyRegistry)
		{
			UE_LOG(LogTemp, Error, TEXT(“Failed to create CelestialObjectManager!”)
		}
		else
		{
		    UE_LOG(LogTemp, Display, TEXT(“Created CelestialObjectManager!”)
		}
	}
}
```

The `StartPlay` function calls the `Initialize` function to start the simulation.

The `Initialize` function creates the `CelestialBodyRegistry`
and displays a message if the registry was successfully created or an error if the registry could not be created.

Now we can use the GameMode class to control the simulation and register and manage the celestial bodies.

------------------------------------------------------------------------------------------------------------

<a name="Expanding-the-CelestialBody-class"></a>
##### Expanding the CelestialBody Class

To use the celestial bodies in the simulation,
we need to extend the `CelestialBody` class to enable the registration and management of the celestial bodies.

To do this, we add a function to register and manage the celestial bodies.

The function should be implemented in the header file `CelestialBody.h` and in the source file `CelestialBody.cpp` as follows:

```cpp
	void AddObjectToRegistry();
```

The implementation of the function should look like this in the source file `CelestialBody.cpp`:

```cpp
  void ACelestialBody::AddBodyToRegistry()
{
	ADemoOrbitSimulation_GameMode* GameMode = Cast<ADemoOrbitSimulation_GameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		ACelestialBodyRegistry* Registry = GameMode->GetCelestialBodyRegistry();
		if (Registry)
		{
			Registry->OnCelestialBodyAdded.Broadcast(this);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to get CelestialObjectManager from Game Mode!);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to cast Game Mode!);
	}
}
```

The function `AddBodyToRegistry` calls the GameMode to get the `CelestialBodyRegistry`
and add the celestial body by calling the delegate `OnCelestialBodyAdded`.

This adds the celestial body to the registry and can be used in the simulation.

To do this, we need to call the function `AddBodyToRegistry` in the `BeginPlay` function of the `CelestialBody` class.

The implementation of the function should look like this in the source file `CelestialBody.cpp`:

```cpp
void ACelestialBody::BeginPlay()
{
    Super::BeginPlay();
    
    SetCurrentVelocity(InitialVelocity);
    MassCalculation();
    
    FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ACelestialBody::AddBodyToRegistry, 0.5f, false);
}
```

The function `AddBodyToRegistry` is called after a delay of 0.5 seconds
to ensure that the registry is ready to register the celestial body.

Now we can use the celestial bodies in the simulation and calculate the orbits.

------------------------------------------------------------------------------------------------------------

<a name="orbitsimulation-class"></a>
##### OrbitSimulation Class

Next, we create the class that performs the simulation of the celestial bodies and the calculation of the orbits.
To do this, we create a new C++ class derived from `AActor` and add the necessary properties and functions.

The header file `OrbitSimulation.h` should look like this:

```cpp
#pragma once

#include “CoreMinimal.h”
#include “GameFramework/Actor.h”
#include “OrbitSimulation.generated.h”

UCLASS()
class SOLARSYSTEM_API AOrbitSimulation : public AActor
{
	GENERATED_BODY()

public:
	AOrbitSimulation();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
```

We will deal with the source file `OrbitSimulation.cpp` later.

<a name="orbitsimulation-properties"></a>
###### *OrbitSimulation Properties:*

Now let's add the properties to define the simulation.

We need the following properties:

- Bool for switching on the manual timescale (for changing the time scale (start, stop, accelerate))
- Time scale

The properties for the simulation should look like this:

```cpp
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = “Physics”)
	bool bManualTimeScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = “Physics”)
	float TimeScale;
	
	UPROPERTY()
	ACelestialBodyRegistry* CelestialBodyRegistry;

```

The timescale bool is editable in the blueprint so that we can start, stop and accelerate the simulation.

The timescale can be edited in the blueprint so that we can speed up or slow down the simulation.

The `CelestialBodyRegistry` property is used to register and manage the celestial bodies.

<a name="orbitsimulation-functions"></a>
###### *OrbitSimulation Functions:*

Now we add the functions to control the simulation and calculate the orbits.

The functions in the header file `OrbitSimulation.h` should look like this:

```cpp
private:

	void UpdateAllObjects(const float& TimeStep) const;
	void UpdateAllPositions(const float& TimeStep) const;
	void UpdateAllVelocities(const float& TimeStep) const;

	FVector CalculateGravitationalAcceleration(const FVector& OtherPosition, const ACelestialBody* Object) const;
	
	void GetCelestialObjectManager();
```

The implementation of the update functions should look like this in the source file `OrbitSimulation.cpp`:

```cpp
void AOrbitSimulation::UpdateAllObjects(const float& TimeStep) const
{
	if (CelestialBodyRegistry)
	{
		UpdateAllPositions(TimeStep);
		UpdateAllVelocities(TimeStep);
	}
	else
	{
		UE_LOG(LogTemp, error, TEXT(“CelestialObjectManager is nullptr! In Orbit Simulation!”);
	}
	
}

void AOrbitSimulation::UpdateAllPositions(const float& TimeStep) const
{
	for (const auto& Body : CelestialBodyRegistry->GetCelestialObjects())
	{
		Body->UpdatePosition(TimeStep);
	}
}

void AOrbitSimulation::UpdateAllVelocities(const float& TimeStep) const
{
	for (const auto& Body : CelestialBodyRegistry->GetCelestialObjects())
	{
		FVector Acceleration = CalculateGravitationalAcceleration(Body->GetActorLocation(), Body);
		Body->UpdateVelocity(Acceleration, TimeStep);
	}
}
```

The function `UpdateAllObjects` calls the update functions for the positions and velocities of the celestial objects.

The function `UpdateAllPositions` updates the positions of the celestial objects based on the current speed and time interval.

The function 'UpdateAllVelocities'
updates the velocities of the celestial bodies based on the gravitational acceleration and the time interval.

The implementation of the function `CalculateGravitationalAcceleration` should look like this in the source file `OrbitSimulation.cpp`:

```cpp
FVector AOrbitSimulation::CalculateGravitationalAcceleration(const FVector& OtherPosition, const ACelestialBody* Object) const
{
    // g = G * M / r^2 | Gravitational acceleration

	FVector Acceleration = FVector::ZeroVector;
	for (const auto& Obj : CelestialBodyRegistry->GetCelestialObjects())
	{
		if (Obj == Object) continue;

		// Gravitational constant G
		const float G = FUniverse::GravitationalConstant;
		// Mass of the sample object m
		const float M = Obj->GetMass();
		// Distance between two objects r = |r1 - r2| r = R
		FVector R = Obj->GetActorLocation() - OtherPosition;
		// Distance squared
		const float SqrR = R.SizeSquared();
		// Direction of the force
		FVector ForceDir = R.GetSafeNormal();

		Acceleration += ForceDir * G * M / SqrR;
	}
	
	return Acceleration;
}
```

The function `CalculateGravitationalAcceleration` calculates the gravitational acceleration based on the gravitational constant,
the mass and the position of the celestial bodies.
For this purpose, the gravitational constant `G`, the mass `M`,
the distance `R` and the distance squares `SqrR` are calculated to determine the gravitational acceleration.

The gravitational acceleration is calculated for each celestial body and summed to obtain the total acceleration.

Next, we add the function `GetCelestialObjectRegistry` to get and initialize the `CelestialBodyRegistry`.

The implementation of the function should look like this in the source file `OrbitSimulation.cpp`:

```cpp
void AOrbitSimulation::GetCelestialObjectRegistry()
{
	AOrbitSimulation_GameMode* GameMode = Cast<AOrbitSimulation_GameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		CelestialBodyRegistry = GameMode->GetCelestialBodyRegistry();
		if (!CelestialBodyRegistry)
		{
			UE_LOG(LogTemp, Display, TEXT("Something went wrong! Failed to create CelestialObjectRegistry! In Orbit Simulation!”)
		}
	}
	else
	{
		UE_LOG(LogTemp, error, TEXT(“Failed to cast Game Mode! In Orbit Simulation!”)
	}
}
```

The function `GetCelestialObjectRegistry` calls the GameMode to get and initialize the `CelestialBodyRegistry`.

The function is called in the `BeginPlay` to initialize the registry.

The implementation of the function should look like this in the source file `OrbitSimulation.cpp`:

```cpp
void AOrbitSimulation::BeginPlay()
{
    Super::BeginPlay();
    
    GetCelestialObjectRegistry();
}
```

Finally, we add the `Tick` function to control the simulation and calculate the orbits.

The implementation of the function should look like this in the source file `OrbitSimulation.cpp`:

```cpp
void AOrbitSimulation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	DeltaTime = FUniverse::TimeStep;
	const float ScaledDeltaTime = bManualTimeScale ? DeltaTime * TimeScale : DeltaTime;
	UpdateAllObjects(ScaledDeltaTime);
}
```

The constant `FUniverse::TimeStep` is used as a time interval for the simulation
and can be adjusted to control the simulation.

By setting the scalable DeltaTime, the simulation can be controlled to increase or decrease the speed of the simulation.

Now we can calculate the orbits of the celestial bodies and create a simulation.

<a name="expanding-the-game-mode-class"></a>
#### Expanding the Game-Mode Class

To start the simulation and to register and manage the celestial bodies, we need to extend the GameMode class.

The implementation of the function should look like this in the source file `OrbitSimulation_GameMode.cpp`:

```cpp
void ADemoOrbitSimulation_GameMode::Initialize()
{
	UWorld* World = GetWorld();
	if (World)
	{
		CelestialBodyRegistry = World->SpawnActor<ACelestialBodyRegistry>();
		if (!CelestialBodyRegistry)
		{
			UE_LOG(LogTemp, error, TEXT("Failed to create CelestialObjectManager! (DemoOrbitSimulation_GameMode)”)
		}
		else
		{
			UE_LOG(LogTemp, display, TEXT("Created CelestialBodyRegistry! (DemoOrbitSimulation_GameMode)”)
		}
		OrbitSimulation = World->SpawnActor<AOrbitSimulation>();
		if (!OrbitSimulation)
		{
			UE_LOG(LogTemp, error, TEXT("Failed to create OrbitSimulation! (DemoOrbitSimulation_GameMode)”)
		}
		else
		{
			UE_LOG(LogTemp, display, TEXT("Created OrbitSimulation! (DemoOrbitSimulation_GameMode)”)
		}
	}
}
```

We add the `OrbitSimulation` property to control the simulation and calculate the orbits.

------------------------------------------------------------------------------------------------------------

<a name="creating-the-simulation"></a>
## Creating the Simulation

<a name="creating-the-level"></a>
### Creating the Level

In the engine in the Content Browser, we create a folder called `Maps`.
In the folder, we create a new level file,
e.g. `SolarSystemSimulation`, by right-clicking on the `Maps` folder and then clicking on `Level`.

<a name="adding-the-game-mode"></a>
##### *Adding the Game-Mode:*

We can set the GameMode in the World Settings of the level
to start the simulation and to register and manage the celestial bodies.

<a name="adding-the-celestial-bodies"></a>
### Adding the Celestial Bodies

To use the celestial bodies in the simulation, we need a basic blueprint and material for the celestial bodies.

<a name="creating-the-base-blueprint"></a>
##### *Creating the Base Blueprint:*

Let's create a base blueprint for the celestial bodies
by right-clicking on the Blueprints folder we created earlier and then clicking on Blueprint Class.
We search for `CelestialBody` and select the class as parent class.
We name the class e.g. `BP_CelestialBodyBase`.

As static mesh for the celestial bodies we use a sphere,
which we create in the editor and set as static mesh for the celestial body.

This means that we do not have to create a new blueprint for each celestial body,
but can use the basic blueprint and configure the properties in the editor.

<a name="creating-the-base-material"></a>
##### *Creating the Base Material:*

Let's
create a base material for the celestial bodies
by right-clicking on the `Materials` folder we created earlier and then clicking on `Material`.
We name the material e.g. `M_CelestialBodySurfaceBase`.
We add three parameters to the material as an absolute base:
- Base Color
- Metallic
- Roughness

The material is used as the base for the celestial bodies and can be configured as an instance for the celestial bodies in the editor.




------------------------------------------------------------------------------------------------------------
<a name="resources"></a>
## Resources

- Unreal Engine 5.3.2
- Visual Studio 2022, JetBrains Rider, or another IDE with C++ support