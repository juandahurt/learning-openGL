cmake_minimum_required(VERSION 3.27)
project(5_textures)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(5_textures main.cpp
        VertexBuffer.h
        VertexBuffer.cpp
        IndexBuffer.h
        IndexBuffer.cpp
        VertexBufferLayout.h
        VertexBufferLayout.cpp
        VertexArray.h
        VertexArray.cpp
        Shader.h
        Shader.cpp
        core.h
        Renderer.cpp
        vendor/stb_image/stb_image.cpp
        Texture.h
        Texture.cpp)

find_package(PkgConfig)

set(CMAKE_CXX_FLAGS "-framework OpenGL")

# GLFW
pkg_check_modules(GLFW REQUIRED glfw3)
target_include_directories(5_textures PRIVATE ${GLFW_INCLUDE_DIRS})
target_link_directories(5_textures PRIVATE ${GLFW_LIBRARY_DIRS})
target_link_libraries(5_textures ${GLFW_LIBRARIES})

# GLEW
pkg_check_modules(GLEW REQUIRED glew)
target_include_directories(5_textures PRIVATE ${GLEW_INCLUDE_DIRS})
target_link_directories(5_textures PRIVATE ${GLEW_LIBRARY_DIRS})
target_link_libraries(5_textures ${GLEW_LIBRARIES})

# GLM
pkg_check_modules(GLM REQUIRED glm)
target_include_directories(5_textures PRIVATE ${GLM_INCLUDE_DIRS})