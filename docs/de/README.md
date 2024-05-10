﻿# Sonnensystem Simulation (Unreal Engine 5.3.2)

Ein interaktives Sonnensystem-Projekt in der Unreal Engine, konzipiert als praktische Einführung in C++, Spielephysik und grundlegende Engine-Konzepte. 
Dieses Repository dient als Plattform, um durch die Entwicklung eines Orbitalsimulationsprojekts tiefe Einblicke in die Programmierung 
mit der Unreal Engine zu gewinnen und dabei sowohl grundlegende als auch fortgeschrittene Konzepte der Spieleentwicklung zu erforschen.

Hinweis: Das Projekt ist in laufender Entwicklung und kann Änderungen und Aktualisierungen unterliegen.

## Inhaltsverzeichnis

- [Einführung](#einführung)
- [Eigenschaften](#eigenschaften)
- [Erste Schritte](#erste-schritte)
  - [Grundlegende Klassen Implementieren](#grundlegende-klassen-implementieren)
    - [CelestialBody Klasse](#celestialbody-klasse)
      - [Properties](#celestialbody-properties)
      - [Mesh Initialisierung](#mesh-initialisierung)
      - [Getter- und Setter-Funktionen](#getter--und-setter-funktionen)
      - [Physikfunktionen](#physikfunktionen)
      - [Gravitationskonstante / Universe Struktur](#gravitationskonstante)
    - [CelestialBodyRegistry Klasse](#celestialbodyregistry-klasse)
      - [Delegaten](#celestialbodyregistry-delegaten)
      - [Properties](#celestialbodyregistry-properties)
      - [Funktionen](#celestialbodyregistry-funktionen)
    - [Game-Mode Klasse](#game-mode-klasse)
      - [Erweiterung der CelestialBody Klasse](#erweiterung-der-celestialbody-klasse)
    - [OrbitSimulation Klasse](#orbitsimulation-klasse)
      - [Properties](#orbitsimulation-properties)
      - [Funktionen](#orbitsimulation-funktionen)
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

------------------------------------------------------------------------------------------------------------

<a name="grundlegende-klassen-implementieren"></a>
### Grundlegende Klassen Implementieren

<a name="celestialbody-klasse"></a>
##### CelestialBody Klasse

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


<a name="celestialbody-properties"></a>
###### *CelestialBody Properties:*

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


<a name="mesh-initialisierung"></a>
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

<a name="getter-und-setter-funktionen"></a>
###### *Getter- und Setter-Funktionen:*

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


<a name="physikfunktionen"></a>
###### *Physikfunktionen:*

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

Die Funktion `UpdateVelocity` berechnet die Geschwindigkeit des Himmelskörpers basierend auf der Beschleunigung und dem Zeitintervall.

Die Funktion `UpdatePosition` aktualisiert die Position des Himmelskörpers basierend auf der aktuellen Geschwindigkeit und dem Zeitintervall.
Die Geschwindigkeit wird mit dem Zeitintervall multipliziert, um die Position des Himmelskörpers zu aktualisieren und die Bewegung über die Mesh-Komponente zu steuern.

Die Funktion `MassCalculation` berechnet die Masse des Himmelskörpers basierend auf den `Radius` und der Gravitationskonstante<sup>*</sup> `G`.
Die Formel für die Masse-Berechnung lautet:
`m = r² * G` oder `Masse = Radius * Radius * G`.
Das Ergebnis wird in der Masse-Property gespeichert und die Masse der Mesh-Komponente überschrieben.

Jetzt setzten wir im Konstruktor den Radius und in der Funktion `BeginPlay` die aktuelle Geschwindigkeit und berechnen die Masse des Himmelskörpers.

Die Implementierung der Funktionen sollte in der Quelldatei `CelestialBody.cpp` wie folgt aussehen:

```cpp
ACelestialBody::ACelestialBody()
{
    PrimaryActorTick.bCanEverTick = true;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;
    MeshComponent->SetSimulatePhysics(true);
    MeshComponent->SetEnableGravity(false);

    SetRadius();
}

void ACelestialBody::BeginPlay()
{
    Super::BeginPlay();
    
    SetCurrentVelocity(InitialVelocity);
    MassCalculation();
}
```

<a name="gravitationskonstante"></a>
##### Gravitationskonstante:

<sup>*</sup> Die Gravitationskonstante `G` und die Struktur `FUniverse` definieren wir in der neu erstellten Header-Datei `Universe.h`.

Die Header-Datei `Universe.h` sollte wie folgt aussehen:

```cpp
#pragma once

#include "CoreMinimal.h"

struct FUniverse
{
	static constexpr float GravitationalConstant = 0.1f; // 6.67430e-11f | m^3 kg^-1 s^-2
	static constexpr float TimeStep = 0.1f;
};
```

Die Gravitationskonstante und Zeitschrittgröße wird als `constexpr` definiert, um sie zur Kompilierzeit zu berechnen und als Konstante zu verwenden.

Die Gravitationskonstante wird als `0.1f` definiert, um die Simulation zu vereinfachen und die Werte zu skalieren.

Für die Simulation verwenden wir eine feste Zeitschrittgröße von `0.1f`, um die Simulation zu steuern und die Orbits zu berechnen.


------------------------------------------------------------------------------------------------------------

<a name="celestialbodyregistry-klasse"></a>
##### CelestialBodyRegistry Klasse

Als Nächstes erstellen wir die Klasse, die die Himmelskörper registriert und verwaltet, um sie in der Simulation zu verwenden.
Dazu erstellen wir eine neue C++ Klasse, die von `AActor` abgeleitet ist und fügen die notwendigen Properties und Funktionen hinzu.

Die Header-Datei `CelestialBodyRegistry.h` sollte wie folgt aussehen:

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ACelestialBodyRegistry.generated.h"

UCLASS()
class SOLARSYSTEM_API ACelestialBodyRegistry : public AActor
{
	GENERATED_BODY()

public:
	ACelestialBodyRegistry();
};
```

<a name="celestialbodyregistry-delegaten"></a>
###### *CelestialBodyRegistry Delegaten:*

Der Delegat `FCelestialObjectAddedDelegate` wird definiert, um das Hinzufügen von Himmelskörpern zu ermöglichen.

Die Delegaten-Definition sollte in der Header-Datei `CelestialBodyRegistry.h` direkt über der Klassendefinition wie folgt aussehen:

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

Die Implementierung des Delegaten sollte in der Quelldatei bzw. Konstruktor `CelestialBodyRegistry.cpp` wie folgt aussehen:

```cpp
#include "ACelestialBodyRegistry.h"


ACelestialBodyRegistry::ACelestialBodyRegistry()
{
	OnCelestialBodyAdded.AddDynamic(this, &ACelestialBodyRegistry::AddCelestialObject);
}
```

Der Delegat `OnCelestialBodyAdded` ist im Blueprint zugänglich und wird im Konstruktor initialisiert, um das Hinzufügen von Himmelskörpern zu ermöglichen.
Wir können den Delegaten verwenden, um Himmelskörper in einer anderen Klasse zu registrieren und zu verwalten.

<a name="celestialbodyregistry-properties"></a>
###### *CelestialBodyRegistry Properties:*

Jetzt fügen wir erstmal die Properties hinzu, um die Himmelskörper zu registrieren.

- Delegaten für das Hinzufügen von Himmelskörpern (siehe oben)
- Array für die Himmelskörper

Die Properties für die Himmelskörper-Registry sollten folgendermaßen aussehen:

```cpp
public:
	ACelestialBodyRegistry();

	UPROPERTY(BlueprintAssignable)
	FCelestialObjectAddedDelegate OnCelestialBodyAdded;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Celestial Objects")
	TArray<ACelestialBody*> CelestialBodies;
```

Das Array `CelestialBodies` ist nur lesbar und enthält alle registrierten Himmelskörper.

Damit wir die ACelestialBody-Pointer verwenden können, müssen wir die `CelestialBody.h` inkludieren.

Die Include-Direktive sollte in der Quelldatei `CelestialBodyRegistry.h` (evtl. mit Ordnerstruktur) wie folgt aussehen:

```cpp
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CelestialBody.h"
#include "ACelestialBodyRegistry.generated.h"
```

<a name="celestialbodyregistry-functionen"></a>
###### *CelestialBodyRegistry Funktionen:*

Jetzt fügen wir die Funktionen hinzu, um die Himmelskörper zu registrieren und zu verwalten.

Die Funktionen sollten folgendermaßen aussehen:

```cpp
public:
	UFUNCTION()
	void AddCelestialObject(ACelestialBody* CelestialObject);
	
	void RemoveCelestialObject(ACelestialBody* CelestialObject);
	
	TArray<ACelestialBody*> GetCelestialObjects() const { return CelestialBodies; }
```

Die Getter-Funktion `GetCelestialObjects` ist `inline` und gibt das Array der Himmelskörper zurück, damit wir auf die Himmelskörper zugreifen können.

Die Implementierung der anderen Funktionen sollte in der Quelldatei `CelestialBodyRegistry.cpp` wie folgt aussehen:

```cpp
#include "ACelestialBodyRegistry.h"


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

In der Funktion `AddCelestialObject` wird der Himmelskörper hinzugefügt, wenn er nicht `nullptr` ist und noch nicht im Array enthalten ist.

In der Funktion `RemoveCelestialObject` wird der Himmelskörper entfernt, wenn er im Array enthalten ist.

------------------------------------------------------------------------------------------------------------

<a name="game-mode-klasse"></a>
##### Game-Mode Klasse

Um die Klassen zu erweitern, müssen wir erstmal eine GameMode-Klasse erstellen, in dem wir die Simulation steuern und die Himmelskörper registrieren und verwalten.
In der GameMode-Klasse initialisieren wir die Simulation und fügen die Himmelskörper hinzu, um die Orbits zu berechnen und die Simulation zu steuern.

Dazu erstellen wir eine neue C++ Klasse, die von `AGameModeBase` abgeleitet ist und fügen die notwendigen Properties und Funktionen hinzu.

Die Header-Datei `OrbitSimulation_GameMode.h` sollte wie folgt aussehen:

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ACelestialBodyRegistry.h"
#include "OrbitSimulation_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class SOLARSYSTEM_API ADemoOrbitSimulation_GameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Celestial Objects")
	ACelestialBodyRegistry* CelestialBodyRegistry;


public:
	virtual void StartPlay() override;
	
	ACelestialBodyRegistry* GetCelestialBodyRegistry() const { return CelestialBodyRegistry; }

	
private:
	void Initialize();
	
};
```

Wir haben die `CelestialBodyRegistry`-Property, eine `inline` Getter-Funktion für die Registry und die Funktion `Initialize`, um die Simulation zu initialisieren, hinzugefügt.

Die Implementierung der Funktion sollte in der Quelldatei `OrbitSimulation_GameMode.cpp` wie folgt aussehen:

```cpp
#include "OrbitSimulation_GameMode.h"


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
			UE_LOG(LogTemp, Error, TEXT("Failed to create CelestialObjectManager!")
		}
		else
		{
		    UE_LOG(LogTemp, Display, TEXT("Created CelestialObjectManager!")
		}
	}
}
```

Die Funktion `StartPlay` ruft die `Initialize`-Funktion auf, um die Simulation zu starten.

Die Funktion `Initialize` erstellt die `CelestialBodyRegistry` und gibt eine Meldung aus, wenn die Registry erfolgreich erstellt wurde oder einen Fehler, wenn die Registry nicht erstellt werden konnte.

Jetzt können wir die GameMode-Klasse verwenden, um die Simulation zu steuern und die Himmelskörper zu registrieren und zu verwalten.

------------------------------------------------------------------------------------------------------------


<a name="erweiterung-celestialbody-klasse"></a>
##### Erweiterung der CelestialBody Klasse:

Um die Himmelskörper in der Simulation zu verwenden, müssen wir die `CelestialBody`-Klasse erweitern, um die Registrierung und Verwaltung der Himmelskörper zu ermöglichen.

Dazu fügen wir eine Funktion hinzu, um die Himmelskörper zu registrieren und zu verwalten.

Die Funktion sollte in der Header-Datei `CelestialBody.h` und in der Quelldatei `CelestialBody.cpp` wie folgt implementiert werden:

```cpp
	void AddObjectToRegistry();
```

Die Implementierung der Funktion sollte in der Quelldatei `CelestialBody.cpp` wie folgt aussehen:

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

Die Funktion `AddBodyToRegistry` ruft den GameMode auf, um die `CelestialBodyRegistry` zu erhalten und den Himmelskörper hinzuzufügen, indem der Delegat `OnCelestialBodyAdded` aufgerufen wird.

Dadurch wird der Himmelskörper zur Registry hinzugefügt und kann in der Simulation verwendet werden.

Dafür müssen wir noch die Funktion `AddBodyToRegistry` in der `BeginPlay` Funktion der `CelestialBody`-Klasse aufrufen.

Die Implementierung der Funktion sollte in der Quelldatei `CelestialBody.cpp` wie folgt aussehen:

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

Die Funktion `AddBodyToRegistry` wird nach einer Verzögerung von 0,5 Sekunden aufgerufen, um sicherzustellen, dass die Registry bereit ist, den Himmelskörper zu registrieren.

Jetzt können wir die Himmelskörper in der Simulation verwenden und die Orbits berechnen.

------------------------------------------------------------------------------------------------------------

<a name="orbitsimulation-klasse"></a>
##### OrbitSimulation Klasse

Als Nächstes erstellen wir die Klasse, die die Simulation der Himmelskörper und die Berechnung der Orbits durchführt.
Dazu erstellen wir eine neue C++ Klasse, die von `AActor` abgeleitet ist und fügen die notwendigen Properties und Funktionen hinzu.

Die Header-Datei `OrbitSimulation.h` sollte wie folgt aussehen:

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OrbitSimulation.generated.h"

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

Um die Quelldatei `OrbitSimulation.cpp` kümmern wir uns später.

<a name="orbit-simulation-properties"></a>
###### *OrbitSimulation Properties:*

Jetzt fügen wir erstmal die Properties hinzu, um die Simulation zu definieren.

Wir benötigen folgende Properties:

- Bool für das Einschalten der manuellen Zeitskala (für das Umstellen der Zeitskala (Start, Stop, Beschleunigen))
- Zeitskala

Die Properties für die Simulation sollten folgendermaßen aussehen:

```cpp
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
	bool bManualTimeScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
	float TimeScale;
	
	UPROPERTY()
	ACelestialBodyRegistry* CelestialBodyRegistry;

```

Die Zeitskala Bool ist im Blueprint editierbar, damit wir die Simulation starten, stoppen und beschleunigen können.

Die Zeitskala ist im Blueprint editierbar, damit wir die Simulation beschleunigen oder verlangsamen können.

Die `CelestialBodyRegistry`-Property wird verwendet, um die Himmelskörper zu registrieren und zu verwalten.

<a name="orbit-simulation-functions"></a>
###### *OrbitSimulation Funktionen:*

Jetzt fügen wir die Funktionen hinzu, um die Simulation zu steuern und die Orbits zu berechnen.

Die Funktionen in der Header-Datei `OrbitSimulation.h` sollten folgendermaßen aussehen:

```cpp
private:

	void UpdateAllObjects(const float& TimeStep) const;
	void UpdateAllPositions(const float& TimeStep) const;
	void UpdateAllVelocities(const float& TimeStep) const;

	FVector CalculateGravitationalAcceleration(const FVector& OtherPosition, const ACelestialBody* Object) const;
	
	void GetCelestialObjectManager();
```

Die Implementierung der Update-Funktionen sollte in der Quelldatei `OrbitSimulation.cpp` wie folgt aussehen:

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
		LOG_DISPLAY("CelestialObjectManager is nullptr! In Orbit Simulation!");
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

Die Funktion `UpdateAllObjects` ruft die Update-Funktionen für die Positionen und Geschwindigkeiten der Himmelskörper auf.

Die Funktion `UpdateAllPositions` aktualisiert die Positionen der Himmelskörper basierend auf der aktuellen Geschwindigkeit und dem Zeitintervall.

Die Funktion `UpdateAllVelocities` aktualisiert die Geschwindigkeiten der Himmelskörper basierend auf der Gravitationsbeschleunigung und dem Zeitintervall.

Die Implementierung der Funktion `CalculateGravitationalAcceleration` sollte in der Quelldatei `OrbitSimulation.cpp` wie folgt aussehen:

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

Die Funktion `CalculateGravitationalAcceleration` berechnet die Gravitationsbeschleunigung basierend auf der Gravitationskonstante, der Masse und der Position der Himmelskörper.
Dazu wird die Gravitationskonstante `G`, die Masse `M`, die Distanz `R` und die Distanzquadrate `SqrR` berechnet, um die Gravitationsbeschleunigung zu bestimmen.

Die Gravitationsbeschleunigung wird für jeden Himmelskörper berechnet und aufsummiert, um die Gesamtbeschleunigung zu erhalten.

Als Nächstes fügen wir die Funktion `GetCelestialObjectManager` hinzu, um die `CelestialBodyRegistry` zu erhalten und zu initialisieren.

Die Implementierung der Funktion sollte in der Quelldatei `OrbitSimulation.cpp` wie folgt aussehen:

```cpp
void AOrbitSimulation::GetCelestialObjectManager()
{
	ADemoOrbitSimulation_GameMode* GameMode = Cast<ADemoOrbitSimulation_GameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		CelestialBodyRegistry = GameMode->GetCelestialBodyRegistry();
		if (!CelestialBodyRegistry)
		{
			UE_LOG(LogTemp, Display, TEXT("Something went wrong! Failed to create CelestialObjectManager! In Orbit Simulation!")
		}
	}
	else
	{
		UE_LOG(LogTemp, error, TEXT("Failed to cast Game Mode! In Orbit Simulation!")
	}
}
```

Die Funktion `GetCelestialObjectManager` ruft den GameMode auf, um die `CelestialBodyRegistry` zu erhalten und zu initialisieren.

Die Funktion wird in der `BeginPlay` aufgerufen, um die Registry zu initialisieren.

Die Implementierung der Funktion sollte in der Quelldatei `OrbitSimulation.cpp` wie folgt aussehen:

```cpp
void AOrbitSimulation::BeginPlay()
{
    Super::BeginPlay();
    
    GetCelestialObjectManager();
}
```

Als Letztes fügen wir die Funktion `Tick` hinzu, um die Simulation zu steuern und die Orbits zu berechnen.

Die Implementierung der Funktion sollte in der Quelldatei `OrbitSimulation.cpp` wie folgt aussehen:

```cpp
void AOrbitSimulation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	DeltaTime = FUniverse::TimeStep;
	const float ScaledDeltaTime = bManualTimeScale ? DeltaTime * TimeScale : DeltaTime;
	UpdateAllObjects(ScaledDeltaTime);
}
```

Die Konstante `FUniverse::TimeStep` wird als Zeitintervall für die Simulation verwendet und kann angepasst werden, um die Simulation zu steuern.

Durch das Setzten der skalierbaren DeltaTime kann die Simulation gesteuert werden, um die Geschwindigkeit der Simulation zu erhöhen oder zu verringern.

Jetzt können wir die Simulation starten und die Orbits der Himmelskörper berechnen.


------------------------------------------------------------------------------------------------------------
<a name="einsatzmittel"></a>
## Einsatzmittel

- Unreal Engine 5.3.2
- Visual Studio 2022, JetBrains Rider oder ein anderer IDE mit C++ Unterstützung