cmake_minimum_required(VERSION 3.27)
project(7_multiple_objects)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(7_multiple_objects
        src/main.cpp
        src/core.h
        src/renderer.cpp
        src/index_buffer.cpp
        src/vertex.cpp
        src/vertex_array.cpp
        src/vertex_buffer.cpp
        src/vertex_buffer_layout.cpp
        src/shader.cpp
        src/world/camera.h
        src/world/cube.cpp
        src/world/cube.h
        src/world/cube.h
        src/world/cube.h
)

set(CMAKE_CXX_FLAGS "-framework OpenGL")

find_package(PkgConfig)

# GLFW
pkg_check_modules(GLFW REQUIRED glfw3)
target_include_directories(7_multiple_objects PRIVATE ${GLFW_INCLUDE_DIRS})
target_link_directories(7_multiple_objects PRIVATE ${GLFW_LIBRARY_DIRS})
target_link_libraries(7_multiple_objects ${GLFW_LIBRARIES})

# GLEW
pkg_check_modules(GLEW REQUIRED glew)
target_include_directories(7_multiple_objects PRIVATE ${GLEW_INCLUDE_DIRS})
target_link_directories(7_multiple_objects PRIVATE ${GLEW_LIBRARY_DIRS})
target_link_libraries(7_multiple_objects ${GLEW_LIBRARIES})

# GLM
pkg_check_modules(GLM REQUIRED glm)
target_include_directories(7_multiple_objects PRIVATE ${GLM_INCLUDE_DIRS})