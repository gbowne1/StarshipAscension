# StarshipAscension

A text-based space game written in C++17.

Version: 0.0.1

Copyright 2025 Gregory Bowne

## Features
- Title screen, login/register, main menu
- New game, resume, load/save games and config
- Captain's log with timestamps
- Navigation, scanners, weapons, shields, engines, health, scoring
- Settings, help
- Progress bars, colors (ANSI), sound (\a)
- Terminal resize support (min 80x25)
- Command line flags: --version, --help, --no-color
- Open source MIT on GitHub (upload to your repo)

## Build
- CMake: mkdir build; cd build; cmake .. -DCMAKE_BUILD_TYPE=Release; make
- Makefile: make
- bash: ./build.sh release
- Meson: meson build; cd build; ninja

Requires CMake 3.10+, g++, glog (for logging).

## Install dependencies in Ubuntu and Debian family Operating Systems for building this game
./install-ubuntu-deps.sh

## Run
./run.sh

## TODO
- Add multiplayer
- Expand game world
- Unit tests with gtest
