# Solar System Simulation (Unreal Engine 5.3.2)

An interactive solar system project in Unreal Engine, designed as a hands-on to C++, game physics, and engine fundamentals.
This repository serves as a platform to gain deep insights into Unreal Engine programming through the development of an orbital simulation project,
exploring both basic and advanced concepts of game development.

Disclaimer: The project is a work in progress and may be subject to changes and updates.

## Table of Contents

- [Features](#features)
- [Introduction](#introduction)
- [Getting Started](#getting-started)
- [Resources](#resources)

<a name="introduction"></a>
## Introduction

The project enables hands-on learning of Unreal Engine's core elements such as the gameplay framework, physics, user interfaces, and input handling. 
By implementing a planetary simulation, programmers can improve their C++ skills and develop an understanding of the architecture and functionality of a game engine.

The step-by-step guide leads from the basics, like setting up a project and creating C++ classes, to advanced topics such as physics calculations and procedural generation. 
Best practices and conventions for programming with the Unreal Engine are conveyed throughout the process.

The goal is to gain a deep understanding of Unreal development through a concrete project, which can also be transferred to other areas of application. 
The repository is intended to serve as a reference and starting point for own experiments and extensions.

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

1. In the engine, click on "Tools" -> "New C++ Class".
2. Choose a class derived from a base class, e.g., `AActor` or `None` for an empty class, useful for utility classes.
3. Choose Public or Private for the access level and select a name for the class.
4. Click "Create Class".
5. Click "Yes" to regenerate the project files.
6. Click "Compile" to compile the class.

Note: The engine automatically generates the header and source files for the new class and adds them to the project.
Compiling the class creates the binary files and makes the class available in the editor. In Unreal, it is important to recompile the class after each change.

<a name="resources"></a>
## Resources

- Unreal Engine 5.3.2
- Visual Studio 2022, JetBrains Rider, or another IDE with C++ support