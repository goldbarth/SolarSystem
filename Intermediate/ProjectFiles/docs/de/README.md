# Sonnensystem Simulation (Unreal Engine 5.3.2)

Ein interaktives Sonnensystem-Projekt in der Unreal Engine, konzipiert als praktische Einführung in C++, Spielephysik und grundlegende Engine-Konzepte. 
Dieses Repository dient als Plattform, um durch die Entwicklung eines Orbitalsimulationsprojekts tiefe Einblicke in die Programmierung 
mit der Unreal Engine zu gewinnen und dabei sowohl grundlegende als auch fortgeschrittene Konzepte der Spieleentwicklung zu erforschen.

Hinweis: Das Projekt ist in laufender Entwicklung und kann Änderungen und Aktualisierungen unterliegen.

## Inhaltsverzeichnis

- [Einführung](#einführung)
- [Eigenschaften](#eigenschaften)
- [Erste Schritte](#erste-schritte)
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

Grundlegende C++ Kenntnisse werden vorausgesetzt und ein grundlegendes Verständnis von Spieleentwicklung und der Unreal Engine ist von Vorteil.

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
Eventuell wird z.B. mit einem Raumfahrzeug und weiterer Physik erweitert um eine immersive Erfahrung zu schaffen. Es kann sich in der Entwicklung noch viel ändern und wird dokumentiert.

<a name="erste-schritte"></a>
## Erste Schritte

##### Erstellen eines neuen Projekts in der Unreal Engine 5.3.2

1. Starte Unreal Engine und wähle unter Games "Blank" als Projektvorlage und C++ als Projekt Defaults.
2. Wähle einen Speicherort für das Projekt, wähle ein Namen und klicke auf "Create Project".

##### Erstellen einer neuen C++ Klasse

1. In der Engine klicke auf "Tools" -> "New C++ Class".
2. Wähle eine Klasse, die von einer Basisklasse abgeleitet ist, z.B. `AActor` oder `None` für eine leere Klasse, praktisch für Utility-Klassen.
3. Wähle Public oder Private für die Zugriffsebene und wähle ein Namen für die Klasse.
4. Klicke auf "Create Class".
5. Klicke auf "Yes" um die Projektdateien neu zu generieren.
6. Klicke auf "Compile" um die Klasse zu kompilieren.

Hinweis: Die Engine generiert automatisch die Header- und Quelldateien für die neue Klasse und fügt sie dem Projekt hinzu.
Das Kompilieren der Klasse erstellt die Binärdateien und macht die Klasse im Editor verfügbar. In Unreal ist es wichtig, die Klasse nach jeder Änderung neu zu kompilieren.

<a name="einsatzmittel"></a>
## Einsatzmittel

- Unreal Engine 5.3.2
- Visual Studio 2022, JetBrains Rider oder ein anderer IDE mit C++ Unterstützung