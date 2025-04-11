cmake_minimum_required(VERSION 3.5)

project(Filing-missing-data-using-interpolation
        VERSION 0.5.0
        LANGUAGES CXX)

enable_testing()

set(CMAKE_PREFIX_PATH "C:/Users/Dell/.vcpkg-clion/vcpkg/installed/x64-mingw-dynamic")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package(Matplot++ CONFIG REQUIRED)
find_package(Catch2 3 REQUIRED)

add_subdirectory(Libs/Cubicspline)

add_library(LinearInterpolation STATIC Src/LinearInterpolation.cpp)
target_compile_features(LinearInterpolation PUBLIC cxx_std_20)
target_include_directories(LinearInterpolation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Inc)
target_link_libraries(LinearInterpolation PRIVATE Point Data Linspain)

add_library(CubicSplineInterpolation STATIC Src/CubicSplineInterpolation.cpp)
target_compile_features(CubicSplineInterpolation PUBLIC cxx_std_20)
target_include_directories(CubicSplineInterpolation PUBLIC Inc)
target_link_libraries(CubicSplineInterpolation PRIVATE Point Data)

add_library(LagrangePolynomialInterpolation STATIC Src/LagrangePolynomialInterpolation.cpp)
target_compile_features(LagrangePolynomialInterpolation PUBLIC cxx_std_20)
target_include_directories(LagrangePolynomialInterpolation PUBLIC Inc)
target_link_libraries(LagrangePolynomialInterpolation PRIVATE Point Data)

add_subdirectory(../Data-clustering/Libs/Point
        ${CMAKE_BINARY_DIR}/Point-build)

add_subdirectory(../Data-clustering/Libs/Data
        ${CMAKE_BINARY_DIR}/Data-build)

add_subdirectory(../Data-clustering/Libs/Linspain
        ${CMAKE_BINARY_DIR}/Linspain-build)

add_subdirectory(../Data-clustering/Libs/Files_tools
        ${CMAKE_BINARY_DIR}/Files_tools-build)

add_subdirectory(../Data-clustering/Libs/Ploting_tools
        ${CMAKE_BINARY_DIR}/Ploting_tools-build)

add_subdirectory(../Data-clustering/Libs/Data_tools
        ${CMAKE_BINARY_DIR}/Data_tools-build)

find_package(Catch2 CONFIG REQUIRED)

add_executable(my_tests
        Tests/CubicSplinelInterpolation_tests.cpp
        Tests/LagrangePolynomialInterpolation_tests.cpp
        Tests/LineInterpolation_tests.cpp
        ../Data-clustering/Libs/Linspain/Tests/Linspain_tests.cpp
        Libs/Cubicspline/Tests/Cubicspline_tests.cpp)

target_compile_features(my_tests PRIVATE cxx_std_20)
target_include_directories(my_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Inc)
target_link_libraries(my_tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(my_tests PRIVATE Point)
target_link_libraries(my_tests PRIVATE Data)
target_link_libraries(my_tests PRIVATE LagrangePolynomialInterpolation)
target_link_libraries(my_tests PRIVATE CubicSplineInterpolation)
target_link_libraries(my_tests PRIVATE LinearInterpolation)
target_link_libraries(my_tests PRIVATE Files_tools)
target_link_libraries(my_tests PRIVATE Ploting_tools)

include(CTest)
include(Catch)
catch_discover_tests(my_tests)

add_executable(my_app main.cpp)
target_compile_features(my_app PRIVATE cxx_std_20)
target_include_directories(my_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Inc)
target_link_libraries(my_app PRIVATE Point)
target_link_libraries(my_app PRIVATE Data)
target_link_libraries(my_app PRIVATE LagrangePolynomialInterpolation)
target_link_libraries(my_app PRIVATE CubicSplineInterpolation)
target_link_libraries(my_app PRIVATE LinearInterpolation)
target_link_libraries(my_app PRIVATE Files_tools)
target_link_libraries(my_app PRIVATE Ploting_tools)
target_link_libraries(my_app PRIVATE Matplot++::cimg  Matplot++::matplot)

