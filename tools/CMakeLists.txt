add_executable(iterate iterate.cpp)
target_link_libraries(iterate PUBLIC mandel)
set_property(TARGET iterate PROPERTY FOLDER Tools)
