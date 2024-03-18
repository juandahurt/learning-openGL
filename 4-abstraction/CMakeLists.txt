cmake_minimum_required(VERSION 3.27)
project(4_abstraction)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(4_abstraction main.cpp
        VertexBuffer.h
        VertexBuffer.cpp
        IndexBuffer.h
        IndexBuffer.cpp
        VertexBufferLayout.h
        VertexBufferLayout.cpp
        VertexArray.h
        VertexArray.cpp
        Shader.h
        Shader.cpp)

find_package(PkgConfig)

set(CMAKE_CXX_FLAGS "-framework OpenGL")

# GLFW
pkg_check_modules(GLFW REQUIRED glfw3)
target_include_directories(4_abstraction PRIVATE ${GLFW_INCLUDE_DIRS})
target_link_directories(4_abstraction PRIVATE ${GLFW_LIBRARY_DIRS})
target_link_libraries(4_abstraction ${GLFW_LIBRARIES})

# GLEW
pkg_check_modules(GLEW REQUIRED glew)
target_include_directories(4_abstraction PRIVATE ${GLEW_INCLUDE_DIRS})
target_link_directories(4_abstraction PRIVATE ${GLEW_LIBRARY_DIRS})
target_link_libraries(4_abstraction ${GLEW_LIBRARIES})
