cmake_minimum_required(VERSION 3.27)
project(1_hello_world)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(1_hello_world main.cpp)

find_package(PkgConfig)

set(CMAKE_CXX_FLAGS "-framework OpenGL")

# GLFW
pkg_check_modules(GLFW REQUIRED glfw3)
target_include_directories(1_hello_world PRIVATE ${GLFW_INCLUDE_DIRS})
target_link_directories(1_hello_world PRIVATE ${GLFW_LIBRARY_DIRS})
target_link_libraries(1_hello_world ${GLFW_LIBRARIES})

# GLEW
pkg_check_modules(GLEW REQUIRED glew)
target_include_directories(1_hello_world PRIVATE ${GLEW_INCLUDE_DIRS})
target_link_directories(1_hello_world PRIVATE ${GLEW_LIBRARY_DIRS})
target_link_libraries(1_hello_world ${GLEW_LIBRARIES})