# Solar System Simulation (Unreal Engine 5.3.2)

An interactive solar system project in Unreal Engine, designed as a hands-on to C++, game physics, and engine fundamentals.
This repository serves as a platform to gain deep insights into Unreal Engine programming through the development of an orbital simulation project,
exploring both basic and advanced concepts of game development.

Disclaimer: The project is a work in progress and may be subject to changes and updates.

## Table of Contents

- [Features](#features)
- [Introduction](#introduction)
- [Getting Started](#getting-started)
  - [Creating the first Class](#creating-the-first-class) 
- [Resources](#resources)

<a name="introduction"></a>
## Introduction

The project enables hands-on learning of Unreal Engine's core elements such as the gameplay framework, physics, user interfaces, and input handling. 
By implementing a planetary simulation, programmers can improve their C++ skills and develop an understanding of the architecture and functionality of a game engine.

The step-by-step guide leads from the basics, like setting up a project and creating C++ classes, to advanced topics such as physics calculations and procedural generation. 
Best practices and conventions for programming with the Unreal Engine are conveyed throughout the process.

The goal is to gain a deep understanding of Unreal development through a concrete project, which can also be transferred to other areas of application. 
The repository is intended to serve as a reference and starting point for own experiments and extensions.

Basic C++ knowledge, understanding of game development and the Unreal Engine is necessary and required.

<a name="features"></a>
## Features

- Implementation of an interactive solar system simulation
- Use of C++ for programming
- Application of physics and mathematics for the simulation of celestial bodies
- Tool for visualizing orbits and planets
- Customization options for the simulation
- Integration of user interfaces and input handling
- Performance optimization through e.g. task graphs and multithreading, allocator optimization, and burst compiler

Note: The simulation can be extended by implementing additional functions and mechanics to personalize and enhance the project. 
For example, it may be expanded with a spacecraft and further physics to create an immersive experience. 
Much can still change in development and will be documented.

<a name="getting-started"></a>
## Getting Started

##### Creating a New Project in Unreal Engine 5.3.2

1. Launch Unreal Engine and select "Blank" under Games as the project template and C++ as the project defaults.
2. Choose a location for the project, select a name, and click "Create Project".

##### Creating a New C++ Class

1. In the engine, click on "Tools" → "New C++ Class".
2. Choose a class derived from a base class, e.g., `AActor` or `None` for an empty class, useful for utility classes.
3. Choose Public or Private for the access level and select a name for the class.
4. Click "Create Class".
5. Click "Yes" to regenerate the project files.
6. Click "Compile" to compile the class.

Note 1: It is possible to create a new class in the IDE and add it to the project manually.
It is also a good idea to create a clear folder structure to organize the classes.
The classes must be stored in a suitable folder, e.g. `MyGame/Games/MyGame/Source/MyGameClasses` or `MyGame/Source/MyGameClasses`.

Note 2: The engine automatically generates the header and source files for the new class and adds them to the project.
Compiling the class creates the binary files and makes the class available in the editor. In Unreal, it is important to recompile the class after each change.

<a name="creating-the-first-class"></a>
##### Creating the First Class

###### CelestialBody Class Implementation
###### *Properties*

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
For now, let's add the properties to define the celestial bodies.

We need the following properties:
- mass
- radius
- initial velocity
- current velocity

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
```

The mass, radius and initial velocity are editable in the blueprint so that we can configure the celestial bodies in the editor.
The current velocity is read-only, as it changes during the simulation.

We also need a mesh component to make the celestial body visible in the editor and to enable the physics simulation,
in which we set the mesh components mass and get the radius of the component.

The properties for the mesh component should look like this:

```cpp
protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Celestial Body")
    UStaticMeshComponent* MeshComponent;
```


###### *Mesh Initialization*

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


###### *Creating getter and setter functions:*

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
The function `SetRadius` sets the radius of the celestial body to the radius of the mesh component in order to determine the size of the celestial body,
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


###### *Creating physics functions:*

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

The functions 'UpdateVelocity' calculates the velocity of the celestial body based on the acceleration and the time interval.

The 'UpdatePosition' function updates the position of the celestial body based on the current velocity and the time interval.
The velocity is multiplied by the time interval to update the position of the celestial body and control the movement via the mesh component.

The function `MassCalculation` calculates the mass of the celestial body based on the `Radius` and the gravitational constant `G`. The formula for the mass calculation is
`Mass = Radius² * G` or `Mass = Radius * Radius * G`.
The result is saved in the mass property and the mass of the mesh component is overwritten.



<a name="resources"></a>
## Resources

- Unreal Engine 5.3.2
- Visual Studio 2022, JetBrains Rider, or another IDE with C++ support