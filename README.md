# Solar System Simulation (Unreal Engine 5.3.2)

![Solar System Simulation](https://github.com/goldbarth/SolarSystem/blob/goldbarth/media/gifs/camera-pan.gif "Short Impression")

An n-body gravity simulation written in C++ for Unreal Engine 5.3.2, plus an editor tooling suite that predicts and visualizes orbital paths before the simulation is ever started.
The project doubles as a multilingual, step-by-step tutorial on C++, game physics, and engine fundamentals in Unreal.

#### Documentation languages:
[English](docs/en/README.md) | [German](docs/de/README.md) | [Property calculations](docs/calc/README.md)

## What This Project Is

Three things live in this repository, and they build on each other:

1. **The simulation** - a runtime n-body solver where every celestial body pulls on every other one, no scripted orbits, no keyframed paths.
2. **The Orbit Debugger** - an in-editor trajectory predictor that runs the same physics on throwaway copies of your bodies and draws the resulting paths, so you can tune mass, velocity, and distance until the orbits actually close.
3. **The tutorial** - full write-ups in English and German that walk through building all of it from an empty project.

Everything is C++ first.
Blueprints are used only as thin configuration wrappers around the C++ actors.

## The Simulation

### N-body gravity, not a two-body approximation

Each tick, the acceleration on every body is the vector sum of the gravitational pull of all other bodies in the scene (`g = G * M / r^2`, summed by superposition).
Nothing is hardcoded as a "central star".
A moon feels its planet, its planet feels the star, and the star gets nudged back by everything orbiting it.
Add a fourth body and the whole system responds.

Key classes:

| Class | Role |
|---|---|
| `ACelestialBody` | A single planet, moon, or star. Owns mass, radius, initial and current velocity, and its debug line color. |
| `ACelestialBodyRegistry` | Central registry of every body in the scene. Bodies announce themselves through a multicast delegate on spawn. |
| `AOrbitSimulation` | The integrator. Advances all positions, then all velocities, every tick. |
| `AOrbitSimulation_GameMode` | Bootstraps registry and simulation so a level only needs the game mode set. |
| `FUniverse` | The physical constants of this universe: scaled gravitational constant and fixed time step. |

### Self-registering bodies

Bodies are not wired up by hand.
`ACelestialBody` broadcasts itself to the registry via `OnCelestialBodyAdded` shortly after `BeginPlay`, and the registry hands the collected set to the simulation.
Drop a new planet into the level and it participates in the physics with no extra setup.

### Mass derived from geometry

Mass does not have to be guessed.
`ACelestialBody` reads the sphere radius straight off its static mesh bounds and derives mass from it (`Mass = Radius^2 / G`), then pushes that value into the physics body as a mass override.
Scale a planet up in the viewport and it becomes proportionally heavier, which keeps hand-built systems physically coherent.
Mass can still be overridden explicitly when a specific ratio is wanted.

### A tunable universe

- **Scaled gravitational constant** - the real `6.67430e-11` is unusable at Unreal unit scale, so `FUniverse::GravitationalConstant` is scaled to `0.1`.
- **Fixed time step** - the simulation runs on `FUniverse::TimeStep` rather than frame delta, so results do not drift with framerate.
- **Manual time scale** - `bManualTimeScale` and `TimeScale` on `AOrbitSimulation` speed the system up or slow it down for observing long-period orbits without waiting real hours.
- **Engine gravity off** - meshes simulate physics but with built-in gravity disabled; motion comes entirely from the orbital solver via physics linear velocity.

## The Orbit Debugger

Getting a stable orbit by trial and error means pressing Play, watching a planet spiral into its star or fly off into the void, stopping, guessing new numbers, and repeating.
The Orbit Debugger removes that loop.

### How it works

`AOrbitDebug` collects every `ACelestialBody` in the level and copies each into a lightweight `FVirtualBody` struct (mass, position, velocity, color).
It then integrates those virtual bodies forward for N steps using **fourth-order Runge-Kutta (RK4)**, which stays far more faithful over long predictions than the simple Euler step used at runtime.
The resulting point cloud is drawn as the predicted trajectory.

The real actors are never touched.
Nothing moves, nothing is simulated, and the whole thing runs **in the editor without entering Play mode** - `UOrbitDrawComponent` ticks in editor and re-runs the prediction whenever a parameter changes.

### What you tune with it

The debugger answers the question the simulation makes expensive to ask: *given this mass, this distance, and this initial velocity, does the orbit close?*

- Orbit not closing, spiral drifting outward - initial velocity too high for the central mass.
- Path curving into the star - velocity too low, or the central mass too large.
- Wobbling ellipses that never repeat - neighbouring bodies are heavy enough to perturb each other; either accept the chaos or rebalance the masses.

Adjust a planet's velocity or mass, and the drawn path updates immediately.
When the ring closes cleanly on itself, the orbit is stable, and only then does it make sense to hit Play.

### Draw modes

- **Debug paths** - raw `DrawDebugPoint` / `DrawDebugLine` output, cheap and immediate, good for fast iteration.
- **Spline paths** - real `USplineComponent` geometry generated per body, giving smooth, clean curves suitable for screenshots and for reasoning about orbit shape.

Both modes use each body's own `LineColor`, so orbits stay visually distinguishable in a crowded system.

### Parameters

| Parameter | Effect | Recommended |
|---|---|---|
| `NumSteps` | How many steps ahead the trajectory is predicted. More steps means longer visible arc. | 100-500 |
| `TimeStep` | How far each prediction step advances. Larger values look further into the future at lower resolution. | 100.0-1000.0 |
| `LineThickness` | Thickness of the drawn line or size of the drawn point. | 0.1-10.0 |
| `bDrawOrbitPaths` | Toggles debug point/line drawing. | - |
| `bDrawSplines` | Toggles spline drawing. | - |

## The Editor Plugin: Orbit Debug Display

A dedicated Slate editor plugin (`Plugins/OrbitDebugDisplay`) puts the debugger behind a proper UI instead of actor properties.

- Adds a **toolbar button** and a **Window menu entry** to the Level Editor.
- Opens a dockable nomad tab with checkboxes for the two draw modes and text fields for line thickness, step count, and time step.
- **Spawns the debug actor on demand** when a control is first used, and **destroys it when the tab is closed** - no stray debug actors left in the level, nothing to remember to clean up.
- Validates every numeric input and shows a Slate notification instead of silently accepting garbage.
- Every control carries a tooltip with the recommended value range.

The result: orbit tuning is a panel you open, adjust, and close, not a workflow built out of selecting actors and hunting through the details panel.

## The Documentation

`docs/` contains far more than API notes.

- **[English](docs/en/README.md)** and **[German](docs/de/README.md)** tutorials - complete walkthroughs from creating an empty UE project to a running, visualized solar system: class design, the gravity math and its derivation, blueprint and material setup, post-process configuration, and orbit debugger usage. Illustrated with the screenshots in `media/images`.
- **[Property calculations](docs/calc/README.md)** - the actual numbers behind the shipped system: body scales derived from real diameters (Mercury as the unit), orbital distances converted from astronomical units to Unreal units, and mass ratios anchored to Earth. Use these to build a system that looks and behaves like the real one, or as a template for inventing your own.

## Repository Layout

```
Source/SolarSystem/
  CelestialBody/     ACelestialBody - a single body, its mass, radius, and velocity
  Orbit/             AOrbitSimulation - the n-body solver, ACelestialBodyRegistry
  DebugTools/        AOrbitDebug (RK4 prediction), UOrbitDrawComponent, FVirtualBody
  GameModes/         AOrbitSimulation_GameMode - wires registry and simulation together
  Structs/           FUniverse - gravitational constant and time step
  Defines/           Logging macros

Plugins/OrbitDebugDisplay/   Slate editor plugin for the orbit debugger

docs/                        Tutorials (en, de) and property calculations
media/                       Screenshots and impression gifs
```

## Getting Started

Requires **Unreal Engine 5.3.2** and a C++ toolchain (Visual Studio, Rider, or equivalent).

Note that `.uproject` and `.uplugin` files are intentionally excluded from version control.
Create a blank C++ project in UE 5.3.2, drop `Source/` and `Plugins/` in, regenerate project files, and compile.
The [English tutorial](docs/en/README.md) covers the full setup, including level, game mode, materials, and post-process configuration.

Recommended first run:

1. Set `AOrbitSimulation_GameMode` as the level's game mode.
2. Place a star and one planet, both derived from `ACelestialBody`.
3. Open the Orbit Debugger from the toolbar, enable spline paths.
4. Adjust the planet's `InitialVelocity` until the predicted orbit closes.
5. Press Play.

## Status

Work in progress.
The physics core and the debugging toolchain are functional; spacecraft, further gameplay physics, and performance work (task graph parallelization of the prediction pass) are on the roadmap.

## License

MIT - see [LICENSE](LICENSE).

## Credits

[Sebastian Lague](https://github.com/SebLague) for the original idea and inspiration.
And of course [Outer Wilds](https://www.mobiusdigitalgames.com/outer-wilds.html) the game, for its inspiration and the idea of the project.
