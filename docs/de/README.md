# Sonnensystem Simulation (Unreal Engine 5.3.2)

Ein interaktives Sonnensystem-Projekt in der Unreal Engine, konzipiert als praktische Einführung in C++, Spielephysik und grundlegende Engine-Konzepte. 
Dieses Repository dient als Plattform, um durch die Entwicklung eines Orbitalsimulationsprojekts tiefe Einblicke in die Programmierung 
mit der Unreal Engine zu gewinnen und dabei sowohl grundlegende als auch fortgeschrittene Konzepte der Spieleentwicklung zu erforschen.

Hinweis: Das Projekt ist in laufender Entwicklung und kann Änderungen und Aktualisierungen unterliegen.

## Inhaltsverzeichnis

- [Einführung](#einführung)
- [Eigenschaften](#eigenschaften)
- [Erste Schritte](#erste-schritte)
  - [Erstellen der ersten Klasse](#erstellen-der-ersten-klasse)
- [Einsatzmittel](#einsatzmittel)

<a name="einführung"></a>
## Einführung

Das Projekt ermöglicht es, die Kernelemente der Unreal Engine wie Gameplay-Framework, Physik, Benutzeroberflächen und Eingabesteuerung praxisnah zu erlernen.
Durch die Implementierung einer Planetensimulation können Programmierer ihre C++-Fähigkeiten verbessern und ein Verständnis für die Architektur und 
Funktionsweise einer Game Engine entwickeln.

Die schrittweise Anleitung führt von den Grundlagen wie dem Aufsetzen eines Projekts und dem Erstellen von C++-Klassen bis hin zu fortgeschrittenen 
Themen wie Physikberechnungen und prozeduraler Generierung. Dabei werden Best Practices und Konventionen für das Programmieren mit der Unreal Engine vermittelt.

Ziel ist es, anhand eines konkreten Projekts ein tiefgehendes Verständnis für die Unreal-Entwicklung zu erlangen, das auch auf andere Anwendungsbereiche übertragbar ist. 
Das Repository soll als Referenz und Ausgangspunkt für eigene Experimente und Erweiterungen dienen.

Grundlegende C++-Kenntnisse, Verständnis für die Entwicklung von Spielen und die Unreal Engine sind notwendig und erforderlich.
<a name="eigenschaften"></a>
## Eigenschaften

- Implementierung einer interaktiven Sonnensystem-Simulation
- Verwendung von C++ für die Programmierung
- Anwendung von Physik und Mathematik für die Simulation von Himmelskörpern
- Tool zur Visualisierung von Orbits und Planeten
- Anpassungsmöglichkeiten für die Simulation
- Integration von Benutzeroberflächen und Eingabesteuerung
- Performance-Optimierung durch z.B. Task Graphs und Multithreading, Allocator-Optimierung und Burst-Compiler

Hinweis: Die Simulation kann durch die Implementierung weiterer Funktionen und Mechaniken erweitert werden, um das Projekt zu personalisieren und zu verbessern. 
Eventuell wird z.B. mit einem Raumfahrzeug und weiterer Physik erweitert, um eine immersive Erfahrung zu schaffen. Es kann sich in der Entwicklung noch viel ändern und wird dokumentiert.

<a name="erste-schritte"></a>
## Erste Schritte

##### Erstellen eines neuen Projekts in der Unreal Engine 5.3.2

1. Starte Unreal Engine und wähle unter Games "Blank" als Projektvorlage und C++ als Projekt Defaults.
2. Wähle einen Speicherort für das Projekt, wähle einen Namen und klicke auf "Create Project".

##### Erstellen einer neuen C++ Klasse

1. In der Engine klicke auf "Tools" → "New C++ Class".
2. Wähle eine Klasse, die von einer Basisklasse abgeleitet ist, z.B. `AActor` oder `None` für eine leere Klasse, praktisch für Utility-Klassen.
3. Wähle Public oder Private für die Zugriffsebene und wähle einen Namen für die Klasse.
4. Klicke auf "Create Class".
5. Klicke auf "Yes" um die Projektdateien neu zu generieren.
6. Klicke auf "Compile" um die Klasse zu kompilieren.

Hinweis 1: Es ist möglich, eine Klasse direkt in der IDE zu erstellen und sie dann dem Projekt hinzuzufügen. 
Es bietet sich auch an eine übersichtliche Ordnerstruktur zu erstellen, um die Klassen zu organisieren.
Die Klasse müssen in einem passenden Ordner abgelegt werden, z.B. `MyGame/Games/MyGame/Source/MyGameClasses` bzw. `MyGame/Source/MyGameClasses`.

Hinweis 2: Die Engine generiert automatisch die Header- und Quelldateien für die neue Klasse und fügt sie dem Projekt hinzu.
Das Kompilieren der Klasse erstellt die Binärdateien und macht die Klasse im Editor verfügbar. In Unreal ist es wichtig, die Klasse nach jeder Änderung neu zu kompilieren.

<a name="erstellen-der-ersten-klasse"></a>
##### Erstellen der ersten Klasse

###### CelestialBody Klasse Implementierung
###### *Properties:*

Als Erstes erstellen wir die Klasse, die als Grundlage für alle Himmelskörper im Sonnensystem dienen wird.
Dazu erstellen wir eine neue C++ Klasse, die von `AActor` abgeleitet ist und fügen die notwendigen Properties und Funktionen hinzu.

Die Header-Datei `CelestialBody.h` sollte wie folgt aussehen:

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

Um die Quelldatei `CelestialBody.cpp` kümmern wir uns später.
Jetzt fügen wir erstmal die Properties hinzu, um die Himmelskörper zu definieren.

Wir benötigen folgende Properties:
- Masse
- Radius
- Initialgeschwindigkeit
- Aktuelle Geschwindigkeit

Die Properties für die Himmelskörper sollten folgendermaßen aussehen:

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

Die Masse, der Radius und die Initialgeschwindigkeit sind im Blueprint editierbar, damit wir die Himmelskörper im Editor konfigurieren können.
Die aktuelle Geschwindigkeit ist nur lesbar, da sie sich während der Simulation ändert.

Außerdem brauchen wir noch eine Mesh-Komponente, um den Himmelskörper im Editor sichtbar zu machen und die Physiksimulation zu ermöglichen, 
in dem wir die Mesh-Komponenten Masse setzen und den Radius der Komponente bekommen.

Die Properties für die Mesh-Komponente sollten folgendermaßen aussehen:

```cpp
protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Celestial Body")
    UStaticMeshComponent* MeshComponent;
```


###### *Mesh Initialisierung:*

Die Mesh-Komponente wird im Konstruktor initialisiert.

Die Konstruktor-Implementierung sollte in der Quelldatei `CelestialBody.cpp` wie folgt aussehen:

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

Der Konstruktor initialisiert die Mesh-Komponente und setzt die Physiksimulation und die Gravitationseinstellungen.
Wir setzen die Physiksimulation auf `true`, damit die Komponente Physiksimulationen durchführt.
Wir setzen die Gravitationseinstellungen auf `false`, da wir unsere eigene Gravitationssimulation implementieren werden.


###### *Erstellen von Getter- und Setter-Funktionen:*

Um auf die Properties der Himmelskörper zuzugreifen und sie zu ändern, erstellen wir Getter- und Setter-Funktionen.

Die Getter- und Setter-Funktionen sollten folgendermaßen aussehen:

```cpp
public:
	float GetMass() const { return Mass; }
	void SetMass(const float& NewMass);

	float GetRadius() const { return Radius; }
	void SetRadius() { Radius = MeshComponent->Bounds.SphereRadius; }

	FVector GetInitialVelocity() const { return InitialVelocity; }
	void SetCurrentVelocity(const FVector& NewVelocity) { CurrentVelocity = NewVelocity; }
```

Bis auf die Funktion `SetMass` sind alle Funktionen inline definiert, da sie nur eine einfache Rückgabe oder Zuweisung durchführen.
Die Funktion `SetRadius` setzt den Radius des Himmelskörpers auf den Radius der Mesh-Komponente, um die Größe des Himmelskörpers zu bestimmen, 
welcher über die größe der Mesh-Komponente definiert wird.

Die Funktion `SetMass` sollte in der Quelldatei `CelestialBody.cpp` wie folgt aussehen:

```cpp
void ACelestialBody::SetMass(const float& NewMass)
{
	Mass = NewMass;
	MeshComponent->SetMassOverrideInKg(NAME_None, Mass, true);
}
```

Die Funktion `SetMass` setzt die Masse des Himmelskörpers und überschreibt die Masse der Mesh-Komponente, um die Masse des Himmelskörpers zu setzen.


###### *Erstellen von Physikfunktionen:*

Um die Physiksimulation zu implementieren, erstellen wir Funktionen, die die Gravitationssimulation und die Bewegung der Himmelskörper berechnen.

Die Funktionen sollten in der Header-Datei `CelestialBody.h` wie folgt aussehen:

```cpp
public:
	void UpdatePosition(const float& TimeStep) const;
	void UpdateVelocity(const FVector& Acceleration, const float& TimeStep);
	
private:
	void MassCalculation();
```

Die Implementierung der Funktionen sollte in der Quelldatei `CelestialBody.cpp` wie folgt aussehen:

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

Die Funktionen `UpdateVelocity` berechnet die Geschwindigkeit des Himmelskörpers basierend auf der Beschleunigung und dem Zeitintervall.

Die Funktion `UpdatePosition` aktualisiert die Position des Himmelskörpers basierend auf der aktuellen Geschwindigkeit und dem Zeitintervall.
Die Geschwindigkeit wird mit dem Zeitintervall multipliziert, um die Position des Himmelskörpers zu aktualisieren und die Bewegung über die Mesh-Komponente zu steuern.

Die Funktion `MassCalculation` berechnet die Masse des Himmelskörpers basierend auf den `Radius` und der Gravitationskonstante `G`. Die Formel für die Masse-Berechnung lautet:
`Masse = Radius² * G` oder `Masse = Radius * Radius * G`.
Das Ergebnis wird in der Masse-Property gespeichert und die Masse der Mesh-Komponente überschrieben.



<a name="einsatzmittel"></a>
## Einsatzmittel

- Unreal Engine 5.3.2
- Visual Studio 2022, JetBrains Rider oder ein anderer IDE mit C++ Unterstützung
