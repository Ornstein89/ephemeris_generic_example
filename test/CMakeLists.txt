cmake_minimum_required(VERSION 3.19)

project(test)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(tests_runner
    tests_runner.cpp
    horizons_results_Moon_Geocenter_1550_2650_equatorialXYZVxVyVz.txt
    IAARAS_Online_Moon_Geocenter_1788_2213_equatorialXYZVxVyVz.txt
)

target_link_libraries(tests_runner PRIVATE GTest::GTest cspice ephaccess)

add_test(NAME tests COMMAND tests_runner)

configure_file(
    horizons_results_Moon_Geocenter_1550_2650_equatorialXYZVxVyVz.txt
    horizons_results_Moon_Geocenter_1550_2650_equatorialXYZVxVyVz.txt
)

configure_file(
    IAARAS_Online_Moon_Geocenter_1788_2213_equatorialXYZVxVyVz.txt
    IAARAS_Online_Moon_Geocenter_1788_2213_equatorialXYZVxVyVz.txt
)

# копирование локальных файлов данных (ядер) с коэффициентами
configure_file(../data/NASA_JPL/naif0012.tls.pc
    naif0012.tls
    COPYONLY)
configure_file(../data/NASA_JPL/de440.bsp
    de440.bsp
    COPYONLY)

# !!! single 3Gb de441.bsp from https://ssd.jpl.nasa.gov/ftp/eph/planets/bsp/
# cause error !!!
#configure_file(../data/NASA_JPL/de441.bsp
#    de441.bsp
#    COPYONLY)

# pair of 1.5Gb de441_part-N.bsp from
# https://naif.jpl.nasa.gov/pub/naif/generic_kernels/spk/planets/
# loaded well
#configure_file(../data/NASA_JPL/de441_part-1.bsp
#    de441_part-1.bsp
#    COPYONLY)
#configure_file(../data/NASA_JPL/de441_part-2.bsp
#    de441_part-2.bsp
#    COPYONLY)

configure_file(../data/EPM2021/epm2021.bsp
    epm2021.bsp
    COPYONLY)
