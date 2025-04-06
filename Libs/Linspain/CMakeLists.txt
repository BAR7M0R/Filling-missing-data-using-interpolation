add_library(Linspain STATIC Src/Linspain.cpp)
target_compile_features(Linspain PUBLIC cxx_std_20)
target_include_directories(Linspain PUBLIC Inc)
target_link_libraries(Linspain PRIVATE Point Data)