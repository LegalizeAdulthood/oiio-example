find_package(OpenImageIO CONFIG REQUIRED)

add_library(mandel
    include/mandel/mandel.h
    mandel.cpp)
target_include_directories(mandel PUBLIC include)
target_compile_options(mandel PUBLIC $<$<CXX_COMPILER_ID:MSVC>:/utf-8>)
target_link_libraries(mandel PUBLIC OpenImageIO::OpenImageIO)
set_property(TARGET mandel PROPERTY FOLDER Libraries)
