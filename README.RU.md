[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT) [![en](https://img.shields.io/badge/lang-en-green.svg)](README.md) [![ru](https://img.shields.io/badge/lang-ru-green.svg)](README.RU.md) [![CMake build Windows/Linux](https://github.com/Ornstein89/ephemeris_generic_example/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/Ornstein89/ephemeris_generic_example/actions/workflows/cmake-multi-platform.yml)

[Readme in English](README.md)

# Базовый пример использования эфемеридных библиотек

## Описание

Код содержит пример расчёта положения тел Солнечной системы с помощью:

1) [эфемерид JPL](https://ssd.jpl.nasa.gov/planets/eph_export.html) (серии DE) и библиотеки NAIF [`CSPICE toolkit`](https://naif.jpl.nasa.gov/naif/toolkit.html).
2) [эфемерид ИПА РАН](https://iaaras.ru/dept/ephemeris/epm/) (серии EPM) с использованием библиотеки [`libephaccess`](https://gitlab.iaaras.ru/iaaras/ephemeris-access).

Библиотека  требует сборки перед подключением в проект. Файл `/libs/CMakeLists.txt` обеспечивает

1) скачивание исходного кода и скомпилированных библиотек `SPICE toolkit` (`CSPICE`) с [сайта разработчика](https://naif.jpl.nasa.gov/naif/toolkit.html) отдельно для Windows и для Linux (мне удалось подключить скачанные статические библиотеки `.lib` и `.a` только в `release`-сборку),
2) сборку статической библиотеки `cspice.lib`/`cspice.a` на локальной машине из скачанных исходников (подходит и для `release`, и для `debug` сборки),
3) докачку файлов данных (ядер) `naif0012.tls` и `de440.bsp` эфемерид `DE440` в каталог `/data/NASA_JPL` (если файлы там отсутствуют),
4) скачивание исходного кода библиотеки `libephaccess` ИПА РАН из [репозитория](https://gitlab.iaaras.ru/iaaras/ephemeris-access),
5) докачку файла данных (ядра) `epm2021.bsp` эфемерид ИПА РАН с официального [FTP-сервера](https://ftp.iaaras.ru/pub/epm/EPM2021/SPICE).

По умолчанию в пример приложения `ephemeris_app` подключается библиотека `cspice.lib`/`cspice.a`, собранная на локальной машине. Для подключения предварительно собранной библиотеки, скачиваемой с [исходным кодом](https://naif.jpl.nasa.gov/naif/toolkit.html), в  [файле `src/CMakeLists.txt`](./src/CMakeLists.txt?plain=1#L33-L41) необходимо закомментировать второй блок кода и раскомментировать первый:

```cmake
# подключение cspice, скачанного с сайта NASA JPL
# target_link_libraries(ephemeris_app
#     PRIVATE
#     ${CSPICE_PREBUILT})

#подключение cspice, собранного на локальной машине в libs/CMakeLists.txt
target_link_libraries(ephemeris_app
    PRIVATE
    cspice)
```

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
```

## Тестирование

Проведено ограниченное тестирование расчёта эфемерид `DE440` и `EPM2021` путём сопоставления данных, рассчитанных в C++-коде с данными, производимыми официальными web-приложениями для расчёта эфемерид:

1) Для тестирования `DE440` в web-приложении [NASA HORIZONS](https://ssd.jpl.nasa.gov/horizons/app.html) были рассчитаны координаты и проекции скорости Луны относительно геоцентра на период `1550-Jan-01`...`2650-Jan-01` в экваториальной системе координат `J2000` с шагом 1 календарный год.
2) Для тестирования `EPM2021` в web-приложении  [Онлайн-служба эфемерид ИПА РАН](https://iaaras.ru/dept/ephemeris/online/) были рассчитаны координаты и проекции скорости Луны относительно геоцентра на период `1788-Jan-01`...`2213-Jan-01` в экваториальной системе координат `J2000` с шагом 1 календарный год.

Тестирование автоматизировано с помощью `gtest` и запускается командой

```bash
ctest
```

после сборки.

По итогам тестирования рассчитанные в C++ координаты совпадают с тестовыми данными с ошибкой не более 1 км, рассчитанные в C++ проекции скорости Луны совпадают с тестовыми данными с ошибкой не более 0,0005 км/с.

## TODO

* [x] Адаптация для сборки в CMake
* [x] Скачивание файлов данных и бибилиотек во время сборки CMake
* [x] CI/CD
* [x] Кроссплатформенная сборка (Windows/Linux)
* [ ] Обновить сборку  в Visual Studio
* [x] Перевод справки
* [ ] Более подробная документация по использованию
* [ ] Юнит-тесты
