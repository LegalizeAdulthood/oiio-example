find_package(OpenImageIO CONFIG REQUIRED)

target_compile_options(OpenImageIO::OpenImageIO INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/utf-8>)

add_library(mandel
    include/mandel/mandel.h
    mandel.cpp)
target_include_directories(mandel PUBLIC include)
target_link_libraries(mandel PUBLIC OpenImageIO::OpenImageIO)
set_property(TARGET mandel PROPERTY FOLDER Libraries)
