cmake_minimum_required(VERSION 3.19)

project(libs VERSION 1.0.0 LANGUAGES C)

#
# JPL NAIF SPICE Toolkit (https://naif.jpl.nasa.gov/naif/toolkit.html)
# Исходный код скачивается сразу с бинарной сборкой под различные платформы.
# В случае необходимости, может быть пересобран из исходного кода с помощью
# пакетного файла makeall.bat, находящегося в корне каталога и запускаемого
# из командной строки Developer Command Prompt for Visual Studio (версия для
# Windows) или аналогичного пакетного файла makeall.csh для командной строки
# Linux
# В сборке библиотеки cspice участвуют файлы из /src/cspice, сборка производится
# пакетным файлом /src/cspice/mkprodct.bat. Все файлы, кроме zzsecprt.c
# собираются с ключами компиляции "/c /O2 -D_COMPLEX_DEFINED -DMSDOS
# -DOMIT_BLANK_CC -DNON_ANSI_STDIO",
# zzsecprt.c собирается с ключами "/c -D_COMPLEX_DEFINED -DMSDOS -DOMIT_BLANK_CC"
# также для статической сборки необходимо добавлять статическое подключение
# С-runtime (ключи компиляции /MT или /MTd), в противном случае isatty() в fio.h
# будет конфликтовать по типу связывания с С-runtime
#

# скачивание и распаковка CSPICE
if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/cspice")
    if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        file(DOWNLOAD
            https://naif.jpl.nasa.gov/pub/naif/toolkit//C/PC_Windows_VisualC_64bit/packages/cspice.zip
            ${CMAKE_CURRENT_SOURCE_DIR}/cspice.zip
        )
        file(ARCHIVE_EXTRACT
            INPUT ${CMAKE_CURRENT_SOURCE_DIR}/cspice.zip
            DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})
        # "tar -xf cspice.zip"
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        file(DOWNLOAD
            https://naif.jpl.nasa.gov/pub/naif/toolkit//C/PC_Linux_GCC_64bit/packages/cspice.tar.Z
            ${CMAKE_CURRENT_SOURCE_DIR}/cspice.tar.Z
        )
        file(ARCHIVE_EXTRACT
            INPUT ${CMAKE_CURRENT_SOURCE_DIR}/cspice.tar.Z
            DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}
        )
    endif()
endif()

file(GLOB
    CSPICE_SOURCES
    cspice/src/cspice/*.c
    cspice/src/cspice/*.h
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")

    # для файла zzsecprt.c ключи компиляции выставляются отдельно согласно
    # оригинальному пакетному файлу для сборки mkprodct.bat
    file(GLOB
        CSPICE_SOURCES2
        cspice/src/cspice/zzsecprt.c
    )
    list(REMOVE_ITEM CSPICE_SOURCES ${CSPICE_SOURCES2})

    if(CMAKE_BUILD_TYPE STREQUAL "Debug")

        # если не выставить стат. связывание CRT - ошибка C2375: isatty: переопределение; другое связывание
        set(CSPICE_COMPILE_FLAGS "/MTd /Od")

        # если не выставить стат. связывание CRT - ошибка C2375: isatty: переопределение; другое связывание
        set(CSPICE_COMPILE_FLAGS_SPECIAL "/MTd /Od")

    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")

        # если не выставить стат. связывание CRT - ошибка C2375: isatty: переопределение; другое связывание
        set(CSPICE_COMPILE_FLAGS "/MT /O2")

        # если не выставить стат. связывание CRT - ошибка C2375: isatty: переопределение; другое связывание
        set(CSPICE_COMPILE_FLAGS_SPECIAL "/MT")

    endif()

    set_source_files_properties(${CSPICE_SOURCES}
        PROPERTIES
        COMPILE_FLAGS ${CSPICE_COMPILE_FLAGS}
        COMPILE_DEFINITIONS "_COMPLEX_DEFINED;MSDOS;OMIT_BLANK_CC;NON_ANSI_STDIO"
    )

    set_source_files_properties(${CSPICE_SOURCES2}
        PROPERTIES
        COMPILE_FLAGS ${CSPICE_COMPILE_FLAGS_SPECIAL}
        COMPILE_DEFINITIONS "_COMPLEX_DEFINED;MSDOS;OMIT_BLANK_CC"
    )

    # вновь объединить все исходники в один список
    list (APPEND CSPICE_SOURCES ${CSPICE_SOURCES2})

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # ключи компиляции и линковки согласно оригинальному пакетному
    # файлу сборки mkprodct.csh
    set(TKCOMPILEOPTIONS "-c -ansi -m64 -O2 -fPIC -DNON_UNIX_STDIO")
    set(TKLINKOPTIONS "-lm -m64")

    add_compile_options(-c)
    add_compile_options(-ansi)
    add_compile_options(-DNON_UNIX_STDIO)
    add_compile_options(-m64)
    add_compile_options(-O2)
    add_compile_options(-fPIC)
    
    add_link_options(-lm)
    add_link_options(-m64)
endif()
# rm -r * && cmake .. && cmake --build . --target cspice
add_library(cspice
    STATIC
    ${CSPICE_SOURCES}
)

target_include_directories(cspice
    PUBLIC
    cspice/src/cspice)

set_target_properties(cspice
    PROPERTIES
    LINKER_LANGUAGE C)


# скачивание файлов данных (ядер), если отсутствуют в каталоге /data
if (NOT EXISTS "${CMAKE_SOURCE_DIR}/data/NASA_JPL/de440.bsp")
    message("/data/NASA_JPL/de440.bsp not exists, downloading")
    file(DOWNLOAD
       https://naif.jpl.nasa.gov/pub/naif/generic_kernels/spk/planets/de440.bsp
       de440.bsp)
else()
    message("/data/NASA_JPL/de440.bsp exists")
endif()

if (NOT EXISTS "${CMAKE_SOURCE_DIR}/data/NASA_JPL/naif0012.tls")
    message("/data/NASA_JPL/naif0012.tls not exists, downloading")
    file(DOWNLOAD
       https://naif.jpl.nasa.gov/pub/naif/generic_kernels/lsk/naif0012.tls
       naif0012.tls)
else()
    message("/data/NASA_JPL/naif0012.tls exists")
endif()


#
# IAA RAS libephaccess (https://gitlab.iaaras.ru/iaaras/ephemeris-access)
# изначально ориентирована на сборку в Visual Studio (Windows) или Make (Linux)
# В данном CMake-файле импортируется как некомпилируемая INTERFACE-библиотека
#

# клонирование исходного кода ephemeris-access IAA RAS
include(FetchContent)
FetchContent_Declare(
    ephaccess
    GIT_REPOSITORY https://gitlab.iaaras.ru/iaaras/ephemeris-access.git
    GIT_TAG  a50da18526b8c9c1d992117f7d6b1653537656bd # master
    # FETCHCONTENT_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR}
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ephemeris-access
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)
FetchContent_MakeAvailable(ephaccess)

set(EPHACCESS_SOURCES
    ephemeris-access/libephaccess/src/ephaccess.c
    ephemeris-access/libephaccess/ephaccess.h
    ephemeris-access/libephaccess/src/daf_reader.c
    ephemeris-access/libephaccess/src/daf_reader.h
)

add_library(ephaccess
    INTERFACE
    ${EPHACCESS_SOURCES}
)

target_include_directories(ephaccess
    INTERFACE
    ephemeris-access/libephaccess)

target_sources(ephaccess
    INTERFACE
    ${EPHACCESS_SOURCES} )


# скачивание файлов данных (ядер), если отсутствуют в каталоге /data
if (NOT EXISTS "${CMAKE_SOURCE_DIR}/data/EPM2021/epm2021.bsp")
    message("/data/EPM2021/epm2021.bsp not exists, downloading")
    file(DOWNLOAD
       https://ftp.iaaras.ru/pub/epm/EPM2021/SPICE/epm2021.bsp
       epm2021.bsp)
else()
    message("/data/EPM2021/epm2021.bsp exists")
endif()
