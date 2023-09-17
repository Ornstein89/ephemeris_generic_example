[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT) [![en](https://img.shields.io/badge/lang-en-green.svg)](README.md) [![ru](https://img.shields.io/badge/lang-ru-green.svg)](README.RU.md) [![CMake build Windows/Linux](https://github.com/Ornstein89/ephemeris_generic_example/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/Ornstein89/ephemeris_generic_example/actions/workflows/cmake-multi-platform.yml)

[Справка на русском](README.RU.md)

# Basic Example of Ephemeris Libraries Use

## Description

The project shows an example of Solar System bodies position and modion calculation with:

1) [JPL ephemeris](https://ssd.jpl.nasa.gov/planets/eph_export.html) (DE-series) with NAIF [`C SPICE` toolkit](https://naif.jpl.nasa.gov/naif/toolkit.html).
2) [IAA RAS ephemeris](https://iaaras.ru/dept/ephemeris/epm/) (EPM-series) with [`libephaccess` library](https://gitlab.iaaras.ru/iaaras/ephemeris-access).

## Build and launch

### Windows

Need to install [CMake*](https://cmake.org/download/) and one of C/C++ build tools (MSVC as part of [Visual Studio Community](https://learn.microsoft.com/ru-ru/cpp/build/vscpp-step-0-installation), for example) first.

*I'm working on alternative build system based on Visual Studio solution only, will be available in the future.

```bat
git clone https://github.com/Ornstein89/ephemeris_generic_example.git
cd ephemeris_generic_example
mkdir build_windows
cd build_windows
cmake .. :: cmake configure for your local machine
cmake --build :: build of all targets: example apps, libs, tests
ctest :: unit testing
```

### Linux

Need to install CMake and C/C++ build tools first:

```bash
sudo apt-get install git g++ gcc build-essential cmake
```

Project build:

```bash
git clone https://github.com/Ornstein89/ephemeris_generic_example.git
cd ephemeris_generic_example
mkdir build_ubuntu
cd build_ubuntu
cmake .. # cmake configure for your local machine
cmake --build # build of all targets: example apps, libs, tests
ctest # unit testing
```

## TODO

* [x] CMake adaptation
* [x] CMake autodownload libs and kernels
* [x] CI/CD
* [x] Crosspaltform build (Windows/Linux)
* [ ] Update Visual Studio build system
* [x] Description internationalization
* [ ] Documentation
* [ ] Testing
