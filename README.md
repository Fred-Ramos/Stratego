# Stratego --- C++ / Qt Project

This project implements **Stratego**, the classical turn-based strategy
board game.\
It includes two independent versions:

-   A **console-only version** (PRE_GUI), fully playable in the
    terminal.\
-   A **graphical client-server version** built with **Qt** (QT_GUI).

The project was developed in 2023 as part of a university course, covering
object-oriented programming, data structures, networking, and GUI
development.

------------------------------------------------------------------------

# PRE_GUI --- Terminal Version (No GUI)

The **PRE_GUI** folder contains the original Stratego implementation
running entirely in the terminal.

## Features

-   ASCII-based board display
-   Both players play **in turns** on the same terminal
-   Moves are entered using coordinates from 00 to 99, where 00 corresponds to the top-left square and 09 to the bottom-left.
-   All Stratego pieces implemented (Spy, Scout, Miner, Bomb, Marshal, etc.)
-   Full movement and combat src
-   Water tiles included
-   Victory/endgame detection using flags and move availability
-   Includes **unit tests** using GoogleTest

## Building

Inside **PRE_GUI**, run:

    cmake -S . -B build
    cmake --build build

## Running unit tests

    ./build/test/Debug/alltests.exe

## Running the game

    .stratego.exe

------------------------------------------------------------------------

# QT_GUI --- Full Graphical Client/Server Game (Qt)

The **QT_GUI** folder contains the graphical version of Stratego,
implemented using **Qt**.\
It consists of **two separate modules**:

1.  **StrategoClient** --- the graphical client used by the players\
2.  **StrategoServer** --- the server that coordinates all game sessions

Multiple player pairs can play simultaneously, with support for
sequences of 5 consecutive games.

# Building

Building the graphical version requires a working installation of **Qt** (Qt 5 or Qt 6).
The project includes both the **StrategoClient** and **StrategoServer** modules.

## Requirements
- Qt installed (Qt Creator recommended)
- Qt Widgets module
- Qt Network module

## Building From Source
1. Open **Qt Creator**
2. Choose *Open Project* and select either:
   - `QT_GUI/StrategoClient/CMakeLists.txt`
   - `QT_GUI/StrategoServer/CMakeLists.txt`
3. Configure the Desktop Qt build kit
4. Build and Run

## Precompiled Binaries
A **precompiled version** of both Server and Client is available in the repository **Releases** section,
and requires **no Qt installation**. Just download and run the executables directly.

------------------------------------------------------------------------

# StrategoServer module

-   Must be launched **before** any clients connect
-   Shows a simple graphical window (no buttons)
-   Displays the **server IP address**
-   Indicates that the server is active and accepting connections
-   Supports several simultaneous matches

To run the server:
Open the project in QtCreator → Build → Run
(or run the generated executable directly)

------------------------------------------------------------------------

# StrategoClient module

-   Each player launches the **StrategoClient** application
-   At startup, the player must enter the **server IP address**
-   Players may **create an account** or **log in**
-   Once connected, all game interactions are handled via the GUI
-   Supports multiple concurrent pairs of players