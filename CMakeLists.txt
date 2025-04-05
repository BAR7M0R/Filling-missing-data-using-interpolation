cmake_minimum_required(VERSION 3.5)

project(data_clustering
        VERSION 0.5.0
        LANGUAGES CXX)

enable_testing()

set(CMAKE_PREFIX_PATH "C:/Users/Dell/.vcpkg-clion/vcpkg/installed/x64-mingw-dynamic")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package(Matplot++ CONFIG REQUIRED)
find_package(Catch2 3 REQUIRED)

add_library(Point STATIC Libs/Point/Src/Point.cpp)
target_compile_features(Point PUBLIC cxx_std_20)
target_include_directories(Point PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Inc)

add_library(Data STATIC Libs/Data/Src/Data.cpp)
target_compile_features(Data PUBLIC cxx_std_20)
target_include_directories(Data PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Inc)
target_link_libraries(Data PUBLIC Point)

add_library(CrispClustering STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/CrispClustering.cpp)
target_compile_features(CrispClustering PUBLIC cxx_std_20)
target_include_directories(CrispClustering PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Inc)
target_link_libraries(CrispClustering PRIVATE Point Data)

add_library(FuzzyClustering STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/FuzzyClustering.cpp)
target_compile_features(FuzzyClustering PUBLIC cxx_std_20)
target_include_directories(FuzzyClustering PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Inc)
target_link_libraries(FuzzyClustering PRIVATE Point Data)

add_library(Files_tools STATIC Libs/Files_tools/Src/Files_tools.cpp)
target_compile_features(Files_tools PUBLIC cxx_std_20)
target_include_directories(Files_tools PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Inc)
target_link_libraries(Files_tools PRIVATE Point Data)

add_library(Ploting_tools STATIC Libs/Ploting_tools/Src/Ploting_tools.cpp)
target_compile_features(Ploting_tools PUBLIC cxx_std_20)
target_include_directories(Ploting_tools PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Inc)
target_link_libraries(Ploting_tools PRIVATE Point Data Matplot++::cimg  Matplot++::matplot)

find_package(Catch2 CONFIG REQUIRED)

add_executable(my_tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/CrispClustering_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/FuzzyClustering_test.cpp
        Libs/Data/tests/Data_test.cpp
        Libs/Point/Tests/Point_test.cpp
        Libs/Files_tools/Tests/Files_tools_test.cpp
        Libs/Ploting_tools/Tests/Ploting_tools_test.cpp)
target_compile_features(my_tests PRIVATE cxx_std_20)
target_include_directories(my_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Inc)
target_link_libraries(my_tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(my_tests PRIVATE Point)
target_link_libraries(my_tests PRIVATE Data)
target_link_libraries(my_tests PRIVATE FuzzyClustering)
target_link_libraries(my_tests PRIVATE CrispClustering)
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
target_link_libraries(my_app PRIVATE CrispClustering)
target_link_libraries(my_app PRIVATE FuzzyClustering)
target_link_libraries(my_app PRIVATE Files_tools)
target_link_libraries(my_app PRIVATE Ploting_tools)
target_link_libraries(my_app PRIVATE Matplot++::cimg  Matplot++::matplot)

