[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT) [![en](https://img.shields.io/badge/lang-en-green.svg)](README.md) [![ru](https://img.shields.io/badge/lang-ru-green.svg)](README.RU.md) [![CMake build Windows/Linux](https://github.com/Ornstein89/ephemeris_generic_example/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/Ornstein89/ephemeris_generic_example/actions/workflows/cmake-multi-platform.yml)

[Readme in English](README.md)

# Внимание! Расчёт эфемерид ещё не протестирован! Работа ведётся! Вы можете использовать этот код на свой собственный риск!

# Базовый пример использования эфемеридных библиотек

## Описание

Код содержит пример расчёта положения тел Солнечной системы с помощью:

1) [эфемерид JPL](https://ssd.jpl.nasa.gov/planets/eph_export.html) (серии DE) и библиотеки NAIF [`CSPICE toolkit`](https://naif.jpl.nasa.gov/naif/toolkit.html).
2) [эфемерид ИПА РАН](https://iaaras.ru/dept/ephemeris/epm/) (серии EPM) с использованием библиотеки [`libephaccess`](https://gitlab.iaaras.ru/iaaras/ephemeris-access).

## TODO

* [x] Адаптация для сборки в CMake
* [x] Скачивание файлов данных и бибилиотек во время сборки CMake
* [x] CI/CD
* [x] Кроссплатформенная сборка (Windows/Linux)
* [ ] Обновить сборку  в Visual Studio
* [x] Перевод справки
* [ ] Более подробная документация по использованию
* [ ] Юнит-тесты
