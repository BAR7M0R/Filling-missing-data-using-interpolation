cmake_minimum_required(VERSION 3.5)

project(Filing-missing-data-using-interpolation
        VERSION 0.5.0
        LANGUAGES CXX)

set(CMAKE_PREFIX_PATH "C:/Users/Dell/.vcpkg-clion/vcpkg/installed/x64-mingw-dynamic")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

option(TESTS "Enable tests" ON)

find_package(Matplot++ CONFIG REQUIRED)

add_subdirectory(../Data-clustering/Libs/Point ${CMAKE_BINARY_DIR}/Point-build)
add_subdirectory(../Data-clustering/Libs/Data ${CMAKE_BINARY_DIR}/Data-build)
add_subdirectory(../Data-clustering/Libs/Linspain ${CMAKE_BINARY_DIR}/Linspain-build)
add_subdirectory(../Data-clustering/Libs/Files_tools ${CMAKE_BINARY_DIR}/Files_tools-build)
add_subdirectory(../Data-clustering/Libs/Ploting_tools ${CMAKE_BINARY_DIR}/Ploting_tools-build)
add_subdirectory(../Data-clustering/Libs/Data_tools ${CMAKE_BINARY_DIR}/Data_tools-build)

add_subdirectory(Libs/LinearInterpolation)
add_subdirectory(Libs/Cubicspline)
add_subdirectory(Libs/CubicSplineInterpolation)
add_subdirectory(Libs/LagrangePolynomialInterpolation)


if(TESTS)
    find_package(Catch2 3 REQUIRED CONFIG)
    enable_testing()
    add_subdirectory(Libs/Cubicspline/Tests)
    add_subdirectory(Libs/LinearInterpolation/Tests)
    add_subdirectory(Libs/CubicSplineInterpolation/Tests)
    add_subdirectory(Libs/LagrangePolynomialInterpolation/Tests)
endif()

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