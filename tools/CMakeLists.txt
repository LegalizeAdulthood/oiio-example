add_executable(oiio-example main.cpp)
target_link_libraries(oiio-example PUBLIC mandel)
set_property(TARGET oiio-example PROPERTY FOLDER Tools)
