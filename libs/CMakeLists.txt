find_package(OpenImageIO CONFIG REQUIRED)

add_library(mandel
    include/mandel/args.h
    include/mandel/iterate.h
    include/mandel/mandel.h
    include/mandel/orbit.h
    args.cpp
    iterate.cpp
    mandel.cpp)
target_include_directories(mandel PUBLIC include)
target_link_libraries(mandel PUBLIC OpenImageIO::OpenImageIO)
set_property(TARGET mandel PROPERTY FOLDER Libraries)
