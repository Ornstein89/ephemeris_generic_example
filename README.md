[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT) [![en](https://img.shields.io/badge/lang-en-green.svg)](README.md) [![ru](https://img.shields.io/badge/lang-ru-green.svg)](README.RU.md) [![CMake build Windows/Linux](https://github.com/Ornstein89/ephemeris_generic_example/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/Ornstein89/ephemeris_generic_example/actions/workflows/cmake-multi-platform.yml)

[Справка на русском](README.RU.md)

# Warning! This repo has no numerical validation yet! Work in progress! You can use the code on your own risk!

# Basic Example of Ephemeris Libraries Use

## Description

The project shows an example of Solar System bodies position and modion calculation with:

1) [JPL ephemeris](https://ssd.jpl.nasa.gov/planets/eph_export.html) (DE-series) with NAIF [`C SPICE` toolkit](https://naif.jpl.nasa.gov/naif/toolkit.html).
2) [IAA RAS ephemeris](https://iaaras.ru/dept/ephemeris/epm/) (EPM-series) with [`libephaccess` library](https://gitlab.iaaras.ru/iaaras/ephemeris-access).

## TODO

* [x] CMake adaptation
* [x] CMake autodownload libs and kernels
* [x] CI/CD
* [x] Crosspaltform build (Windows/Linux)
* [ ] Update Visual Studio build system
* [x] Description internationalization
* [ ] Documentation
* [ ] Testing
