cmake_minimum_required(VERSION 3.19)

project(ephemeris_app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    ephemeris_generic_example.cpp
)

add_executable(ephemeris_app
    ${SOURCES}
)

#подключение cspice, собранного в данном CMake проекте
#target_link_libraries(ephemeris_app
#    PRIVATE
#    cspice)

# альтернативное подключение cspice, предварительно построенной с помощью
# оригинальной пакетной сборки, или скачанной
# !ВНИМАНИЕ при сборке на Linux следует переименовать
# cspice/lib/cspice.a в libcspice.a

include_directories(../libs/cspice/include)
find_library(CSPICE_PREBUILT
    cspice.a
    ../libs/cspice/lib)
message(${CSPICE_PREBUILT})
target_link_libraries(ephemeris_app
    PRIVATE
    ${CSPICE_PREBUILT})

# подключение эфемерид ИПМ РАН
target_link_libraries(ephemeris_app
    PRIVATE
    ephaccess)

# копирование локальных файлов данных (ядер) с коэффициентами
# configure_file(../data/NASA_JPL/naif0012.tls
#     naif0012.tls
#     COPYONLY)
# configure_file(../data/NASA_JPL/de440.bsp
#     de440.bsp
#     COPYONLY)
# configure_file(../data/EPM2021/epm2021.bsp
#     epm2021.bsp
#     COPYONLY)

# альтернативно: скачивание файлов данных
file(DOWNLOAD
   https://naif.jpl.nasa.gov/pub/naif/generic_kernels/lsk/naif0012.tls
   naif0012.tls)
file(DOWNLOAD
   https://naif.jpl.nasa.gov/pub/naif/generic_kernels/spk/planets/de440.bsp
   de440.bsp)
file(DOWNLOAD
   https://ftp.iaaras.ru/pub/epm/EPM2021/SPICE/epm2021.bsp
   epm2021.bsp)

#TODO загрузка файлов по сети
