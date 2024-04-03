cmake_minimum_required(VERSION 3.27)
project(6_perspective)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(6_perspective
        src/main.cpp
        src/renderer.h
        src/renderer.cpp
        src/vertex_buffer.h
        src/vertex_buffer.cpp
        src/vertex_array.h
        src/vertex_array.cpp
        src/vertex_buffer_layout.cpp
        src/vertex_buffer_layout.h
        src/index_buffer.cpp
        src/index_buffer.h
        src/shader.cpp
        src/shader.h
        src/vertex.cpp
        src/vertex.h)

set(CMAKE_CXX_FLAGS "-framework OpenGL")

find_package(PkgConfig)

# GLFW
pkg_check_modules(GLFW REQUIRED glfw3)
target_include_directories(6_perspective PRIVATE ${GLFW_INCLUDE_DIRS})
target_link_directories(6_perspective PRIVATE ${GLFW_LIBRARY_DIRS})
target_link_libraries(6_perspective ${GLFW_LIBRARIES})

# GLEW
pkg_check_modules(GLEW REQUIRED glew)
target_include_directories(6_perspective PRIVATE ${GLEW_INCLUDE_DIRS})
target_link_directories(6_perspective PRIVATE ${GLEW_LIBRARY_DIRS})
target_link_libraries(6_perspective ${GLEW_LIBRARIES})

# GLM
pkg_check_modules(GLM REQUIRED glm)
target_include_directories(6_perspective PRIVATE ${GLM_INCLUDE_DIRS})
