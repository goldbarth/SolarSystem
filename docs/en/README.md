﻿# Solar System Simulation (Unreal Engine 5.3.2)

An interactive solar system project in Unreal Engine, designed as a hands-on to C++, game physics, and engine fundamentals.
This repository serves as a platform to gain deep insights into Unreal Engine programming through the development of an orbital simulation project,
exploring both basic and advanced concepts of game development.

Disclaimer: The project is a work in progress and may be subject to changes and updates.

## Table of Contents

- [Features](#features)
- [Introduction](#introduction)
- [Getting Started](#getting-started)
#### Basic Classes
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
#### Create Simulation
- [Creating the Simulation](#creating-the-simulation)
  - [Creating the level](#creating-the-level)
  - [Adding the game-mode](#adding-the-game-mode)
  - [Add post-processing effects](#add-post-processing-effects)
  - [Adding the celestial bodies](#adding-the-celestial-bodies)
    - [Creating the base blueprint](#creating-the-base-blueprint)
    - [Creating the base material](#creating-the-base-material)
    - [Create celestial bodies](#create-celestial-bodies)
      - [Create the sun](#create-the-sun)
      - [Create the earth](#create-the-earth)
  - [Starting the simulation](#starting-the-simulation)
    - [Configure the simulation](#configure-the-simulation) 
#### Orbit Debugger
- [Visualizing the orbits](#visualizing-the-orbits)
  - [Create the orbit debugger](#create-the-orbit-debugger)
    - [Virtual celestial body struct](#virtual-celestial-body-struct)
    - [Virtual celestial body interface](#virtual-celestial-body-interface)
    - [OrbitDebug component](#orbitdebug-component)
    - [OrbitDebug class](#orbitdebug-class)
      - [Properties](#orbitdebug-properties)
      - [Functions](#orbitdebug-functions)
  - [Using the orbit debugger](#using-the-orbit-debugger)
    - [Create the blueprint](#create-the-orbit-debugger-blueprint)
    - [Configure the debugger](#configure-the-orbit-debugger)
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

#### Creating a New Project in Unreal Engine 5.3.2

1. Launch Unreal Engine and select "Blank" under Games as the project template and C++ as the project defaults.
2. Choose a location for the project, select a name, and click "Create Project"

#### Creating a New C++ Class

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
## Implement Basic Classes

#### CelestialBody Class

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
##### *CelestialBody Properties:*

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Celestial Body")
	float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Celestial Body")
	FVector InitialVelocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Celestial Body")
	FVector CurrentVelocity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug Options")
	mutable FLinearColor LineColor;
```

The mass and initial velocity is editable in the blueprint so that we can configure the celestial bodies in the editor.
The current velocity is read-only, as it changes during the simulation.
The radius is only readable as it results from the size of the mesh component.

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
##### *Mesh Initialization:*

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
##### *Getter and setter functions:*

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
##### *Physics functions:*

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

Now we set the current speed and radius in the `BeginPlay` function and calculate the mass of the celestial body.
As the values can be set in the editor, the functions must be called in the `BeginPlay` function and not in the constructor,
otherwise the values will not be transferred correctly.

The implementation of the functions should look like this in the source file `CelestialBody.cpp`:

```cpp
ACelestialBody::ACelestialBody()
{
    PrimaryActorTick.bCanEverTick = true;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;
    MeshComponent->SetSimulatePhysics(true);
    MeshComponent->SetEnableGravity(false);
}

void ACelestialBody::BeginPlay()
{
    Super::BeginPlay();
 
    SetCurrentVelocity(InitialVelocity);
    SetRadius();
    MassCalculation();
}
```

------------------------------------------------------------------------------------------------------------

<a name="gravitational-constant"></a>
#### Gravitational Constant

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
#### CelestialBodyRegistry Class

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
##### *CelestialBodyRegistry Delegate:*

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
##### *CelestialBodyRegistry Properties:*

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
##### *CelestialBodyRegistry Functions:*

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
#### Game-Mode Class

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
#### Expanding the CelestialBody Class

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
##### *OrbitSimulation Properties:*

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
##### *OrbitSimulation Functions:*

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

The gravitational acceleration is calculated for each celestial body and summed to get the total acceleration.

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

------------------------------------------------------------------------------------------------------------

<a name="expanding-the-game-mode-class"></a>
#### Expanding the Game-Mode Class

To start the simulation and to register and manage the celestial bodies, we need to extend the GameMode class.

The implementation of the function should look like this in the source file `OrbitSimulation_GameMode.cpp`:

```cpp
void AOrbitSimulation_GameMode::Initialize()
{
	UWorld* World = GetWorld();
	if (World)
	{
		CelestialBodyRegistry = World->SpawnActor<ACelestialBodyRegistry>();
		if (!CelestialBodyRegistry)
		{
			UE_LOG(LogTemp, error, TEXT("Failed to create CelestialBodyRegistry! (OrbitSimulation_GameMode)”)
		}
		else
		{
			UE_LOG(LogTemp, display, TEXT("Created CelestialBodyRegistry! (OrbitSimulation_GameMode)”)
		}
		OrbitSimulation = World->SpawnActor<AOrbitSimulation>();
		if (!OrbitSimulation)
		{
			UE_LOG(LogTemp, error, TEXT("Failed to create OrbitSimulation! (OrbitSimulation_GameMode)”)
		}
		else
		{
			UE_LOG(LogTemp, display, TEXT("Created OrbitSimulation! (OrbitSimulation_GameMode)”)
		}
	}
}
```

We add the `OrbitSimulation` property to control the simulation and calculate the orbits.

------------------------------------------------------------------------------------------------------------

<a name="creating-the-simulation"></a>
## Creating the Simulation

<a name="creating-the-level"></a>
#### Creating the Level

In the engine in the Content Browser, we create a folder called `Maps`.
In the folder, we create a new level file,
e.g. `SolarSystemSimulation`, by right-clicking on the `Maps` folder and then clicking on `Level`.

![Creating the Level](https://github.com/goldbarth/SolarSystem/blob/goldbarth/media/images/create-level.png)

<a name="adding-the-game-mode"></a>
##### *Adding the Game-Mode:*

We can set the GameMode in the World Settings of the level
to start the simulation and to register and manage the celestial bodies.

![Adding the Game-Mode](https://github.com/goldbarth/SolarSystem/blob/goldbarth/media/images/add-game-mode.png)


<a name = “add-post-processing-effects”></a>
##### *Add post-processing effects:*

What is noticeable now is that the sun is only shining very faintly.
This is because we have not yet added any post-processing effects.

To do this,
we create a new post-processing volume
by clicking on the plus symbol in the editor via `Volume` and then `Post-Processing Volume`.
The volume is automatically added to the scene, and we can configure the settings in the Details Panel.

![Add Post Processing Volume](https://github.com/goldbarth/SolarSystem/blob/goldbarth/media/images/add-ppv.png)

Two important settings are `Unbound` and `Infinite Extent`,
where we check the box so that the volume works in the entire scene.

![Configure Post Processing Volume 1](https://github.com/goldbarth/SolarSystem/blob/goldbarth/media/images/ppv-unbound.png)


Under Exposure, set the Auto-Exposure `Min EV100` and `Max EV100` to `0`.

![Configure Post Processing Volume 2](https://github.com/goldbarth/SolarSystem/blob/goldbarth/media/images/ppv-auto-exposure.png)

The Auto Exposure setting ensures that the brightness remains the same in every scene.


<a name="adding-the-celestial-bodies"></a>
#### Adding the Celestial Bodies

To use the celestial bodies in the simulation, we need a basic blueprint and material for the celestial bodies.

<a name="creating-the-base-blueprint"></a>
##### *Creating the Base Blueprint:*

Let's create a base blueprint for the celestial bodies
by right-clicking on the Blueprints folder we created earlier and then clicking on Blueprint Class.

![Creating the Base Blueprint](https://github.com/goldbarth/SolarSystem/blob/goldbarth/media/images/bp-base1.png)

We search for `CelestialBody` and select the class as parent class.
We name the class e.g. `BP_CelestialBodyBase`.

![Selecting the Parent Class](https://github.com/goldbarth/SolarSystem/blob/goldbarth/media/images/bp-base2.png)

We use a sphere as the static mesh for the celestial bodies,
which we create in the editor and set as the static mesh for the celestial body.
In the Details Panel under Physics we activate `Simulate Physics` and `Mass (kg)`,
the mass is calculated automatically when the simulation is started.
Finally, we deactivate `Enable Gravity` as we are using our own gravity simulation.

![Configure the base blueprint](https://github.com/goldbarth/SolarSystem/blob/goldbarth/media/images/bp-base3.png)

This means that we do not have to create a new blueprint for each celestial body,
but can use the basic blueprint and configure the properties in the editor.

<a name="creating-the-base-material"></a>
##### *Creating the Base Material:*

Let's
create a base material for the celestial bodies
by right-clicking on the `Materials` folder we created earlier and then clicking on `Material`.
We name the material e.g. `M_CelestialBodySurfaceBase`.

![Creating the Base Material](https://github.com/goldbarth/SolarSystem/blob/goldbarth/media/images/m-base1.png)

We add three parameters to the material as an absolute base:
- `Base Color`
- `Metallic`
- `Roughness`

![Configure base material](https://github.com/goldbarth/SolarSystem/blob/goldbarth/media/images/m-base2.png)

The material is used as the base for the celestial bodies and can be configured as an instance for the celestial bodies in the editor.

Note:
Additional parameters can also be added
or exchanged later to configure the surface of the celestial bodies and add textures.

<a name="create-celestial-bodies"></a>
### *Create Celestial Bodies:*

Let's create the celestial bodies in the editor using the base blueprint and the base material.
We need at least two celestial bodies to start the simulation and calculate the orbits.

<a name="create-the-sun"></a>
##### *Create the Sun:*

Let's start with the sun by creating a new blueprint and using the base blueprint.
To do this,
we create a new blueprint by right-clicking on the `Blueprints` folder and then clicking on `Blueprint Class`.
We search for `BP_CelestialBodyBase` and select the class as Parent Class.

![Create Sun Blueprint](https://github.com/goldbarth/SolarSystem/blob/goldbarth/media/images/bp-sun1.png)

We name the blueprint e.g. `BP_Sun`.

For the sun, we need another material, which we create in the editor and set as material for the sun.
We name the material e.g. `M_SunSurface`.

The material only needs one parameter:
- `Emissive Color`.

![Create sun material](https://github.com/goldbarth/SolarSystem/blob/goldbarth/media/images/m-sun1.png)

The color can be set as desired, but the V value of the HSV color space should be set to 10 so that the sun shines.
We also create an instance of the material to configure the color in the editor.
We name the instance e.g. `MI_SunSurface` or `MI_SunSurface_Inst`.

We create the instance by right-clicking on the base material and then clicking on `Create Material Instance`.

![Create sun material instance](https://github.com/goldbarth/SolarSystem/blob/goldbarth/media/images/m-sun2.png)
![Sun material instance](https://github.com/goldbarth/SolarSystem/blob/goldbarth/media/images/m-sun3.png)
![Configure sun material instance](https://github.com/goldbarth/SolarSystem/blob/goldbarth/media/images/m-sun4.png)

We set the scaling of the mesh to '284.84' and the material to the instance of the material just created.

![Configure Sun 1](https://github.com/goldbarth/SolarSystem/blob/goldbarth/media/images/bp-sun2.png)

The mass (important: in the Celestial Body and not in the Physics settings) to `332.946.000`
and the initial velocity to `0`.

For the sun we set the line color to `FLinearColor(1, 1, 0, 1)` to visualize the orbits.

![Configure Sun 2](https://github.com/goldbarth/SolarSystem/blob/goldbarth/media/images/bp-sun3.png)

Finally,
place the sun in the editor by dragging it into the scene and setting the position in the Details panel to `0, 0, 0`.
This way the sun is in the center of the scene, and the orbits of the celestial bodies are calculated around the sun.


<a name = “create-the-earth”></a>
##### *Create the Earth:*

Let's create the earth by creating a new blueprint and using the base blueprint.

For the earth, we use the base material and create an instance of the material to configure the color in the editor.
We name the instance e.g. `MI_EarthSurface` or `MI_EarthSurface_Inst`.
We create the instance by right-clicking on the base material and then clicking on `Create Material Instance`.

The color can be set as desired.

We set the scaling of the mesh to `2.61` and the initial speed to `16.7`.
The mass is set to `1000` and the line color to `FLinearColor(0, 0, 1, 1)`.

Finally,
we place the earth in the editor by dragging it into the scene
and setting the position in the details panel to `0, 114242, 0`.

![Earth localization](https://github.com/goldbarth/SolarSystem/blob/goldbarth/media/images/bp-earth-location.png)

Note:
The position,
mass and initial speed of the earth are important so that the orbits of the celestial bodies are calculated correctly.
The property calculations can be found under `Resources`.

------------------------------------------------------------------------------------------------------------

<a name="starting-the-simulation"></a>
## Starting the Simulation:

If we now start the simulation, the celestial bodies should circle around the sun and the orbits should be calculated.
As the speed of the simulation depends on the time scale, we can start, stop and accelerate the simulation.

<a name="configure-the-simulation"></a>
#### Configure the Simulation:

At the moment, the only way to change the time scale and properties of the celestial bodies is to 
configure the values in the editor when the simulation is running.

We can do this by starting the simulation in the editor and selecting the `OrbitSimulation` instance in the outliner panel.
![Configure simulation 1](https://github.com/goldbarth/SolarSystem/blob/goldbarth/media/images/sim-config1.png)

In the Details Panel under Physics we can set the `Manual Time Scale` property to `true`.
![Configure Simulation 2](https://github.com/goldbarth/SolarSystem/blob/goldbarth/media/images/sim-config2.png)

We can set the `Time Scale` to a higher value to speed up the simulation or set it to a lower value to slow down the simulation.
![Configure simulation 3](https://github.com/goldbarth/SolarSystem/blob/goldbarth/media/images/sim-config3.png)

------------------------------------------------------------------------------------------------------------

<a name="visualizing-the-orbits"></a>
## Visualizing the Orbits:

Since we are calculating the orbits of the celestial bodies around the sun, but the orbits are not visible,
it makes sense to add an orbit visualization effect or to create a debugger.


<a name="create-the-orbit-debugger"></a>
#### *Create the Orbit Debugger*

For the debugger,
we first need a structure for the virtual celestial bodies so that we do not use the real celestial bodies.
Also, an interface for the virtual celestial bodies
to get the properties of the celestial bodies and set them in the actor component.
The actor component is used to visualize the orbits of the celestial bodies in editor mode (not in game mode).

<a name="virtual-celestial-body-struct"></a>
##### *Virtual Celestial Body Struct:*

The struct for the virtual celestial bodies should look like this in a new header file `FVirtualBody.h`:

```cpp
struct FVirtualBody
{
	float Mass;

	FVector Location;
	FVector Velocity;

	explicit FVirtualBody(const ACelestialBody* Body)
	{
		if (Body)
		{
			Mass = Body->GetMass();
			Location = Body->GetActorLocation();
			Velocity = Body->GetInitialVelocity();
		}
	}
};
```

The `FVirtualBody` structure contains the mass, position and speed of the virtual celestial bodies.

We can use the constructor to transfer the properties of the real celestial bodies to the virtual celestial bodies.

<a name="virtual-celestial-body-interface"></a>
##### *Virtual Celestial Body Interface:*

To do this,
we create a new Unreal C++ class derived from `UInterface` or Interface and add the necessary properties and functions.

The interface for the virtual celestial bodies consists only of a header file `IVirtualBody.h` and should look like this:

```cpp
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IVirtualBody.generated.h"

UINTERFACE(MinimalAPI)
class UVirtualBody : public UInterface
{
	GENERATED_BODY()
};

```

We add `UINTERFACE(MinimalAPI)` to define the interface.

In the second step, we add the functions to get and set the properties of the virtual celestial bodies.

The functions should look like this:

```cpp
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IVirtualBody.generated.h"

UINTERFACE(MinimalAPI)
class UVirtualBody : public UInterface
{
	GENERATED_BODY()
};

class SOLARSYSTEM_API IVirtualBody
{
	GENERATED_BODY()

public:
	virtual bool GetDrawOrbitPaths() const = 0;
	virtual void DrawOrbitPaths() = 0;
};
```

The function `GetDrawOrbitPaths` returns the bool to switch the orbit visualization on and off.
The function `DrawOrbitPaths` is used to visualize the orbits of the celestial bodies.

<a name="orbitdebug-component"></a>
##### *OrbitDebug Component:*

Let's create a new Unreal C++ class derived from `UActorComponent` and add the necessary properties and functions.

The header file `VirtualBodyComponent.h` should look like this:

```cpp
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
```

We add the raw pointer `OrbitDrawer` to use the interface for the virtual celestial bodies.

The source file `VirtualBodyComponent.cpp` should look like this:

```cpp
#include "OrbitDrawComponent.h"

UOrbitDrawComponent::UOrbitDrawComponent() : OrbitDrawer(Cast<IVirtualBody>(GetOwner()))
{
	PrimaryComponentTick.bCanEverTick = true;
	bTickInEditor = true;
}

void UOrbitDrawComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DrawOrbits();
}

void UOrbitDrawComponent::DrawOrbits() const
{
	if (OrbitDrawer && OrbitDrawer->GetDrawOrbitPaths())
	{
		OrbitDrawer->DrawOrbitPaths();
	}
}
```

The constructor initializes the raw pointer `OrbitDrawer` by receiving the interface from the OrbitDebug class.

In the `TickComponent` function, the `DrawOrbits` function is called to visualize the orbits of the celestial bodies.

<a name="orbitdebug-class"></a>
##### *OrbitDebug class:*

Let's create an orbit debugger to visualize the orbits of the celestial bodies.

To do this, we create a new C++ class derived from `AActor` and add the necessary properties and functions.

The header file `OrbitDebug.h` should look like this:

```cpp
#pragma once

#include "CoreMinimal.h"
#include "FVirtualBody.h"
#include "IVirtualBody.h"
#include "OrbitDrawComponent.h"
#include "GameFramework/Actor.h"
#include "OrbitDebug.generated.h"

UCLASS()
class SOLARSYSTEM_API AOrbitDebug : public AActor, public IVirtualBody
{
	GENERATED_BODY()

public:
	AOrbitDebug();
```

The header files for the virtual celestial bodies, the interface and the actor component are used in the OrbitDebug class.
In addition, `IVirtualBody` is implemented as an interface for the virtual celestial bodies.

<a name="orbitdebug-properties"></a>
##### *OrbitDebug Properties:*

Now let's add the properties to visualize the orbits of the celestial bodies.
We need the following properties for this:
- OrbitDrawComponent (actor component for the visualization of the orbits)
- Bool for switching the orbit visualization on and off
- Line thickness (for the visualization of the orbits)
- Number of steps for the orbit (number of points)
- Time interval for the orbit (distance between the points)

The properties for the orbit debugger should look like this:

```cpp
protected:
	AOrbitDebug();
	
	UPROPERTY(VisibleDefaultsOnly)
	UOrbitDrawComponent* OrbitDrawComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbit Debug")
	bool bDrawOrbitPaths;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbit Debug")
	float LineThickness = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbit Debug")
	int NumSteps = 35000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbit Debug")
	float TimeStep = 0.1f;
```

All properties are editable in the blueprint so that we can configure the orbits of the celestial bodies.

The `bDrawOrbitPaths` bool is used to switch the orbit visualization on and off.

The `OrbitDrawComponent` property is used to visualize the orbits of the celestial bodies.

The `NumSteps` property specifies the number of points that are calculated for the orbit.
The `TimeStep` property specifies the time interval used for the orbit.

The `LineThickness` property specifies the thickness of the lines used for the orbit.

<a name="orbitdebug-getter-and-setter"></a>
##### *OrbitDebug getter and setter:*

Now we add the getter and setter functions to get and set the properties.
The getter and setter functions should look like this:

```cpp
public:
	virtual bool GetDrawOrbitPaths() const override { return bDrawOrbitPaths; }
	void SetDrawOrbitPaths(const bool& bNewDrawOrbitPaths) { bDrawOrbitPaths = bNewDrawOrbitPaths; }

	float GetLineThickness() const { return LineThickness; }
	void SetLineThickness(const float& NewLineThickness) { LineThickness = NewLineThickness; }

	int GetNumSteps() const { return NumSteps; }
	void SetNumSteps(const int& NewNumSteps) { NumSteps = NewNumSteps; }

	float GetTimeStep() const { return TimeStep; }
	void SetTimeStep(const float& NewTimeStep) { TimeStep = NewTimeStep; }
```

The getter and setter functions are defined `inline` to get and set the properties of the orbit debugger.

<a name="orbitdebug-functions"></a>
##### *OrbitDebug Functions:*

Next, we add the interface functions.

The functions in the header file `OrbitDebug.h` should look like this:

```cpp
	virtual void DrawOrbitPaths() override;
```

We need the following functions to calculate the orbits of the celestial bodies:

```cpp
private:
	TArray<FVirtualBody> InitializeVirtualBodies(const TArray<AActor*>& Bodies);
	void SimulateOrbits(TArray<FVirtualBody>& VirtualBodies, TArray<FVector>& DrawPoints) const;
	void UpdateVelocities(TArray<FVirtualBody>& VirtualBodies) const;
	void UpdatePositions(TArray<FVirtualBody>& VirtualBodies, TArray<FVector>& DrawPoints, const int& Step) const;
	void DrawPaths(const TArray<FVirtualBody>& VirtualBodies, const TArray<FVector>& DrawPoints, TArray<AActor*> Bodies) const;
	FVector CalculateAcceleration(const int& BodyIndex, const TArray<FVirtualBody>& VirtualBodies) const;
```

The `InitializeVirtualBodies` function initializes the virtual celestial bodies based on the real celestial bodies.

The function `SimulateOrbits` simulates the orbits of the celestial bodies based on the virtual celestial bodies.

The functions `UpdateVelocities` and `UpdatePositions` update the velocities and positions of the virtual celestial bodies.

The function `DrawPaths` visualizes the orbits of the celestial bodies based on the virtual celestial bodies.

The function `CalculateAcceleration` calculates the acceleration of the celestial bodies based on the virtual celestial bodies.


Let's start with the constructor in the source file to initialize the `OrbitDrawComponent`.
The implementation of the function should look like this in the source file `OrbitDebug.cpp`:

```cpp
#include "OrbitDebug.h"

#include "OrbitDrawComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SolarSystem/Structs/Universe.h"

AOrbitDebug::AOrbitDebug()
{
	PrimaryActorTick.bCanEverTick = true;
	OrbitDrawComponent = CreateDefaultSubobject<UOrbitDrawComponent>(TEXT("DebugDraw"));
	RootComponent = OrbitDrawComponent;
}
```

The `OrbitDrawComponent` is created as a sub-object and set as the root component.

The implementation of the function `DrawOrbitPaths` should look like this in the source file `OrbitDebug.cpp`:

```cpp
void AOrbitDebug::DrawOrbitPaths()
{
	const UWorld* World = GetWorld();
	if (World == nullptr) return;
	
	TArray<AActor*> Bodies;
	UGameplayStatics::GetAllActorsOfClass(World, ACelestialBody::StaticClass(), Bodies);
	if (Bodies.Num() == 0) return;
	
	TArray<FVector> DrawPoints;
	DrawPoints.SetNum(Bodies.Num() * GetNumSteps());
	TArray<FVirtualBody> VirtualBodies = InitializeVirtualBodies(Bodies);

	SimulateOrbits(VirtualBodies, DrawPoints);
	DrawPaths(VirtualBodies, DrawPoints, Bodies);
}
```

All celestial bodies in the scene are searched for and stored in the array `Bodies`.
The array `DrawPoints` is initialized,
and the size is set to the number of celestial bodies multiplied by the number of steps.
The array `VirtualBodies` is initialized to store the virtual celestial bodies.

The function `SimulateOrbits` is called to simulate the orbits of the celestial bodies.
The function `DrawPaths` is called to visualize the orbits of the celestial bodies.

The implementation of the function `InitializeVirtualBodies` should look like this in the source file `OrbitDebug.cpp`:

```cpp
TArray<FVirtualBody> AOrbitDebug::InitializeVirtualBodies(const TArray<AActor*>& Bodies)
{
	TArray<FVirtualBody> VirtualBodies;
	VirtualBodies.Reserve(Bodies.Num());
	
	for (const auto& Body : Bodies)
	{
		ACelestialBody* CelestialBody = Cast<ACelestialBody>(Body);
		if (CelestialBody)
		{
			VirtualBodies.Add(FVirtualBody(CelestialBody));
		}
	}
	
	return VirtualBodies;
}
```

The function `InitializeVirtualBodies` initializes the virtual orbits based on the real orbits.

The implementation of the function `SimulateOrbits` should look like this in the source file `OrbitDebug.cpp`:

```cpp
void AOrbitDebug::SimulateOrbits(TArray<FVirtualBody>& VirtualBodies, TArray<FVector>& DrawPoints) const
{
    for (int Step = 0; Step < NumSteps; ++Step)
    {
        UpdateVelocities(VirtualBodies);
        UpdatePositions(VirtualBodies, DrawPoints, Step);
    }
}
```

The function `SimulateOrbits` simulates the orbits of the celestial bodies based on the virtual celestial bodies.

The implementation of the function `UpdateVelocities` should look like this in the source file `OrbitDebug.cpp`:

```cpp
void AOrbitDebug::UpdateVelocities(TArray<FVirtualBody>& VirtualBodies) const
{
	for (int i = 0; i < VirtualBodies.Num(); ++i)
	{
		VirtualBodies[i].Velocity += CalculateAcceleration(i, VirtualBodies) * GetTimeStep();
	}
}
```

The function `UpdateVelocities` updates the velocities of the virtual celestial bodies based on the acceleration and the time interval.

The implementation of the function `UpdatePositions` should look like this in the source file `OrbitDebug.cpp`:

```cpp
void AOrbitDebug::UpdatePositions(TArray<FVirtualBody>& VirtualBodies, TArray<FVector>& DrawPoints, const int& Step) const
{
	for (int i = 0; i < VirtualBodies.Num(); ++i)
	{
		VirtualBodies[i].Location += VirtualBodies[i].Velocity * GetTimeStep();
		DrawPoints[i * GetNumSteps() + Step] = VirtualBodies[i].Location;
	}
}
```


The function `UpdatePositions` updates the positions of the virtual celestial bodies based on the velocities and the time interval.

The implementation of the function `DrawPaths` should look like this in the source file `OrbitDebug.cpp`:

```cpp
void AOrbitDebug::DrawPaths(const TArray<FVirtualBody>& VirtualBodies, const TArray<FVector>& DrawPoints, TArray<AActor*> Bodies) const
{
	for (int i = 0; i < VirtualBodies.Num(); ++i)
	{
		const ACelestialBody* CelestialBody = Cast<ACelestialBody>(Bodies[i]);
		FColor PathColor = CelestialBody->GetLineColor().ToFColor(true);
		if (CelestialBody == nullptr || CelestialBody->ActorHasTag(CentralBodyTag)) continue;
		for (int Steps = 0; Steps < GetNumSteps() - 1; ++Steps)
		{
			FVector Point = DrawPoints[i * GetNumSteps() + Steps];
			DrawDebugPoint(GetWorld(), Point, GetLineThickness(), PathColor, false, -1.0f);
		}
	}
}
```

The `DrawPaths` function visualizes the orbits of the celestial bodies based on the virtual celestial bodies.

It is iterated over all celestial bodies. The color is used by the celestial body, with which the orbit is drawn.

The implementation of the function `CalculateAcceleration` should look like this in the source file `OrbitDebug.cpp`:

```cpp
FVector AOrbitDebug::CalculateAcceleration(const int& BodyIndex, const TArray<FVirtualBody>& VirtualBodies) const
{
	FVector Acceleration = FVector::ZeroVector;

	for (int i = 0; i < VirtualBodies.Num(); ++i)
	{
		if(BodyIndex != i)
		{
			const FVector Direction = VirtualBodies[i].Location - VirtualBodies[BodyIndex].Location;
			const float Distance = Direction.Size();
			const float Force = FUniverse::GravitationalConstant * VirtualBodies[i].Mass * VirtualBodies[BodyIndex].Mass / (Distance * Distance);
			Acceleration += Direction.GetSafeNormal() * (Force / VirtualBodies[BodyIndex].Mass);
		}
	}
	
	return Acceleration;
}
```

The function `CalculateAcceleration` calculates the acceleration of the celestial bodies based on the virtual celestial bodies.

The acceleration is calculated for each celestial body by using the direction, distance and gravitational force.


<a name="using-the-orbit-debugger"></a>
### Using the Orbit Debugger:

<a name="create-the-orbit-debugger-blueprint"></a>
##### *Create the Orbit Debugger Blueprint:*

To use the debugger,
we create a new blueprint by right-clicking on the `Blueprints` folder and then clicking on `Blueprint Class`.
We search for `AOrbitDebug` and select the class as parent class.

![Create Orbit Debugger](https://github.com/goldbarth/SolarSystem/blob/goldbarth/media/images/create-debugger-bp.png)

We can now place the blueprint in the scene and configure the parameters in the editor as required.

![Place Orbit Debugger](https://github.com/goldbarth/SolarSystem/blob/goldbarth/media/images/set-debugger-bp.png)


<a name="configure-the-orbit-debugger"></a>
##### *Configure the Orbit Debugger:*

The `bDrawOrbitPaths` property is used to switch the orbit visualization on and off.
![Configure orbit debugger 1](https://github.com/goldbarth/SolarSystem/blob/goldbarth/media/images/earth-orbit-entry.png)

The `NumSteps` property specifies the number of points that are calculated for the orbit.
![Configure orbit debugger 2](https://github.com/goldbarth/SolarSystem/blob/goldbarth/media/images/earth-orbit-numsteps.png)

The `TimeStep` property specifies the time interval used for the orbit.
![Configure orbit debugger 3](https://github.com/goldbarth/SolarSystem/blob/goldbarth/media/images/earth-orbit-timestep.png)

The `LineThickness` property specifies the thickness of the lines used for the orbit.
![Configure orbit debugger 4](https://github.com/goldbarth/SolarSystem/blob/goldbarth/media/images/earth-orbit-linethickness.png)

Again to visualize the `TimeStep` in combination with the `LineThickness`.
![Configure Orbit Debugger 5](https://github.com/goldbarth/SolarSystem/blob/goldbarth/media/images/earth-orbit-linethickness-timestep.png)

Examples of how the debugger can be used.

![Orbit-Debugger example 1](https://github.com/goldbarth/SolarSystem/blob/goldbarth/media/images/solarsystem-orbits1.png)

![Orbit debugger example 2](https://github.com/goldbarth/SolarSystem/blob/goldbarth/media/images/solarsystem-orbits2.png)

It makes perfect sense to experiment with the celestial body values (radius, mass and initial velocity) and change them.
The calculations in the [Resources](#resources) can help to create a realistic simulation.


------------------------------------------------------------------------------------------------------------

If you want to recreate the solar system as a model, you can configure the celestial bodies and orbits as follows:
[Model calculations](https://github.com/goldbarth/SolarSystem/blob/goldbarth/docs/calc/README.md)

All values (scaling, mass, speed, distance to the sun) for the celestial bodies in the solar system are listed here.

------------------------------------------------------------------------------------------------------------
<a name="resources"></a>
## Resources

- Unreal Engine 5.3.2
- Visual Studio 2022, JetBrains Rider, or another IDE with C++ support
- Unreal Engine Documentation: [UE 5.3](https://dev.epicgames.com/documentation/en-us/unreal-engine/unreal-engine-5-3-documentation)

- Calculations of the properties of celestial bodies and orbits: [Model-Calculations](https://github.com/goldbarth/SolarSystem/blob/goldbarth/docs/calc/README.md)