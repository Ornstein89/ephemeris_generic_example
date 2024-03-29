cmake_minimum_required(VERSION 3.19)

project(ephemeris_app1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    ephemeris_generic_example.cpp
)

add_executable(ephemeris_app1
    ${SOURCES}
)

# подключение cspice (заголовки)
include_directories(../libs/cspice/include)
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")

    find_library(CSPICE_PREBUILT
        cspice
        ../libs/cspice/lib)
    #message(${CSPICE_PREBUILT})

elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")

    find_library(CSPICE_PREBUILT
        cspice.a  # в скачиваемом пакете библиотека названа не libcspice.a, а cspice.a
        ../libs/cspice/lib)
    #message(${CSPICE_PREBUILT})

endif()

# подключение cspice (библиотека), предварительно собранной и скачаннй
# вместе с исходным кодом с сайта NASA JPL
# (https://naif.jpl.nasa.gov/naif/toolkit_C.html)
# (!!!  НЕ ПОДКЛЮЧАЕТСЯ В DEBUG-СБОРКУ !!!)

# target_link_libraries(ephemeris_app1
#     PRIVATE
#     ${CSPICE_PREBUILT})

# альтернативное подключение cspice (библиотеки), собранной на локальной машине
# в libs/CMakeLists.txt
# Может быть собрана и подключена в конфигурации DEBUG
target_link_libraries(ephemeris_app1
    PRIVATE
    cspice)

# подключение эфемерид ИПМ РАН (только исходный код, тип INTERFACE)
target_link_libraries(ephemeris_app1
    PRIVATE
    ephaccess)

# копирование локальных файлов данных (ядер) с коэффициентами
configure_file(../data/NASA_JPL/naif0012.tls
    naif0012.tls
    COPYONLY)
configure_file(../data/NASA_JPL/de440.bsp
    de440.bsp
    COPYONLY)
configure_file(../data/EPM2021/epm2021.bsp
    epm2021.bsp
    COPYONLY)
