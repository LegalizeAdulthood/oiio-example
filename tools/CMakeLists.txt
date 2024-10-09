add_executable(iterate iterate.cpp)
target_link_libraries(iterate PUBLIC mandel)
set_property(TARGET iterate PROPERTY FOLDER Tools)

add_executable(color color.cpp)
target_link_libraries(color PUBLIC mandel)
set_property(TARGET color PROPERTY FOLDER Tools)
