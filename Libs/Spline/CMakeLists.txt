add_library(Spline STATIC Src/Spline.cpp)
target_compile_features(Spline PUBLIC cxx_std_20)
target_include_directories(Spline PUBLIC Inc)
target_link_libraries(Spline PRIVATE Point Data)