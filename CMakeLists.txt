cmake_minimum_required(VERSION 3.27)
project(learning_openGL)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(learning_openGL
        src/example.h
        src/main.cpp
        src/1-hello-world/hello_world.h
        src/2-shader-from-file/shader-from-file.h)

find_package(PkgConfig)

set(CMAKE_CXX_FLAGS "-framework OpenGL")

# GLFW
pkg_check_modules(GLFW REQUIRED glfw3)
target_include_directories(learning_openGL PRIVATE ${GLFW_INCLUDE_DIRS})
target_link_directories(learning_openGL PRIVATE ${GLFW_LIBRARY_DIRS})
target_link_libraries(learning_openGL ${GLFW_LIBRARIES})

# GLEW
pkg_check_modules(GLEW REQUIRED glew)
target_include_directories(learning_openGL PRIVATE ${GLEW_INCLUDE_DIRS})
target_link_directories(learning_openGL PRIVATE ${GLEW_LIBRARY_DIRS})
target_link_libraries(learning_openGL ${GLEW_LIBRARIES})