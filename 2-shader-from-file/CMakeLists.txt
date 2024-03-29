cmake_minimum_required(VERSION 3.27)
project(2_shader_from_file)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(2_shader_from_file main.cpp)

find_package(PkgConfig)

set(CMAKE_CXX_FLAGS "-framework OpenGL")

# GLFW
pkg_check_modules(GLFW REQUIRED glfw3)
target_include_directories(2_shader_from_file PRIVATE ${GLFW_INCLUDE_DIRS})
target_link_directories(2_shader_from_file PRIVATE ${GLFW_LIBRARY_DIRS})
target_link_libraries(2_shader_from_file ${GLFW_LIBRARIES})

# GLEW
pkg_check_modules(GLEW REQUIRED glew)
target_include_directories(2_shader_from_file PRIVATE ${GLEW_INCLUDE_DIRS})
target_link_directories(2_shader_from_file PRIVATE ${GLEW_LIBRARY_DIRS})
target_link_libraries(2_shader_from_file ${GLEW_LIBRARIES})