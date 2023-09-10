[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT) [![en](https://img.shields.io/badge/lang-en-green.svg)](README.md) [![ru](https://img.shields.io/badge/lang-ru-green.svg)](README.RU.md) [![CMake build Windows/Linux](https://github.com/Ornstein89/ephemeris_generic_example/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/Ornstein89/ephemeris_generic_example/actions/workflows/cmake-multi-platform.yml)

[Readme in English](README.md)

# Внимание! Расчёт эфемерид ещё не протестирован! Работа ведётся! Вы можете использовать этот код на свой собственный риск!

# Базовый пример использования эфемеридных библиотек

## Описание

Код содержит пример расчёта положения тел Солнечной системы с помощью:

1) [эфемерид JPL](https://ssd.jpl.nasa.gov/planets/eph_export.html) (серии DE) и библиотеки NAIF [`CSPICE toolkit`](https://naif.jpl.nasa.gov/naif/toolkit.html).
2) [эфемерид ИПА РАН](https://iaaras.ru/dept/ephemeris/epm/) (серии EPM) с использованием библиотеки [`libephaccess`](https://gitlab.iaaras.ru/iaaras/ephemeris-access).

Библиотека `SPICE toolkit` (`CSPICE`) требует сборки перед подключением в проект. Файл `/libs/CMakeLists.txt` обеспечивает

1) скачивание исходного кода и скомпилированных библиотек с сайта разработчика отдельно для Windows и для Linux
2) сборку статической библиотеки `cspice.lib`/`cspice.a` на локальной машине из скачанных исходников

По умолчанию в пример приложения `ephemeris_app` подключается именно скачанная готовая библиотека, для подключения её построенной локально версии в [файле `src/CMakeLists.txt`](./src/CMakeLists.txt?plain=1#L33-L41) необходимо закомментировать первый блок кода и раскомментировать второй

```cmake
# подключение cspice, скачанного с сайта NASA JPL
target_link_libraries(ephemeris_app
    PRIVATE
    ${CSPICE_PREBUILT})

#подключение cspice, собранного на локальной машине в libs/CMakeLists.txt
#target_link_libraries(ephemeris_app
#    PRIVATE
#    cspice)
```

Библиотека `libephaccess` подключается в приложение на уровне исходного кода (но может быть предварительно собрана и подключена как статически, так и динамически). Файл `/libs/CMakeLists.txt` обеспечивает клонирование репозитория библиотеки с открытого GitLab-сервера ИПА РАН.

## Сборка и запуск

### Windows

Предварительно требуется установка [CMake*](https://cmake.org/download/) и одного из компиляторов для C/C++ (к примеру, компилятор MSVC в составе [Visual Studio Community](https://learn.microsoft.com/ru-ru/cpp/build/vscpp-step-0-installation)).

*Ведётся разработка резервной системы сборки без CMake, на основе только Visual Studio.

```bat
git clone https://github.com/Ornstein89/ephemeris_generic_example.git
cd ephemeris_generic_example
mkdir build_windows
cd build_windows
cmake .. # конфигурация cmake-сборки на локальной машине
cmake --build # сборка всех целей: пример приложения, библиотеки, тесты
ctest # запуск автотестирования
```

### Linux

Предварительно требуется установка CMake и инструментов для разработки на C/C++:

```bash
sudo apt-get install git g++ gcc build-essential cmake
```

Сборка проекта:

```bash
git clone https://github.com/Ornstein89/ephemeris_generic_example.git
cd ephemeris_generic_example
mkdir build_ubuntu
cd build_ubuntu
cmake .. # конфигурация cmake-сборки на локальной машине
cmake --build # сборка всех целей: пример приложения, библиотеки, тесты
ctest # запуск автотестирования
```

## Варианты сборки

## TODO

* [x] Адаптация для сборки в CMake
* [x] Скачивание файлов данных и бибилиотек во время сборки CMake
* [x] CI/CD
* [x] Кроссплатформенная сборка (Windows/Linux)
* [ ] Обновить сборку  в Visual Studio
* [x] Перевод справки
* [ ] Более подробная документация по использованию
* [ ] Юнит-тесты
