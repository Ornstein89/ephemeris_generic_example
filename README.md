[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT) [![CMake on multiple platforms](https://github.com/Ornstein89/ephemeris_generic_example/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/Ornstein89/ephemeris_generic_example/actions/workflows/cmake-multi-platform.yml)

# Warning! This repo has no numerical validation yet! Work in progress! You can use the code on your own risk!


# Ephemeris Generic Example

An example of ephemeris calculation with different toolkits and sources: NASA/NAIF SPICE toolkit with JPL DE430 ephemeris and also IAA RAS EPM 2017 ephemeris.

This code can be used as simplified example for students to get familiar of use of astronomical software toolkits:

* `libephaccess` of IAA RAS (https://gitlab.iaaras.ru/iaaras/ephemeris-access)
* SPICE toolkit (CSPICE port for C language) of NASA/NAIF (https://naif.jpl.nasa.gov/naif/toolkit.html)

and ephemeris data source files:

* EPM 2017 ephemeris data files (http://iaaras.ru/en/dept/ephemeris/epm/2017/#4)
* NASA JPL DE430 and in general DE4xx series (https://ssd.jpl.nasa.gov/?planet_eph_export)

## TODO

* [x] CMake adaptation
* [x] CMake autodownload libs and kernels
* [x] CI/CD
* [ ] Crosspaltforming (Windows/Linux)
* [ ] Update Visual Studio build system
* [ ] Internationalization
* [ ] Documentation
* [ ] Testing
