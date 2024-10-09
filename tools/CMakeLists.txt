add_executable(iterate iterate.cpp)
target_link_libraries(iterate PUBLIC mandel)
set_property(TARGET iterate PROPERTY FOLDER Tools)

add_executable(color-iters color.cpp)
target_link_libraries(color-iters PUBLIC mandel)
set_property(TARGET color-iters PROPERTY FOLDER Tools)
