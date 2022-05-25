cmake_minimum_required(VERSION 3.16)
project(OpenGL_course)

find_package(OpenGL REQUIRED)

include_directories(external/glew-2.1.0/include)

set(SUITE1 colorpyramid)

add_executable(${SUITE1}
        main.cpp
        Shader.cpp Shader.h
        Window.cpp Window.h
        Mesh.cpp Mesh.h
        )
target_link_libraries(${SUITE1} PUBLIC glfw glew glm)
set_target_properties(${SUITE1} PROPERTIES
        CXX_STANDARD_REQUIRED ON
        CXX_STANDARD 17
        )

set(GLFW_BUILD_EXAMPLES OFF)
set(BUILD_SHARED_LIBS  ON)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)
set(GLFW_VULKAN_STATIC OFF)

add_subdirectory(external/glfw-3.3.7)
add_subdirectory(external/glew-2.1.0/build/cmake)
add_subdirectory(external/glm)

file(COPY Shaders DESTINATION ${CMAKE_BINARY_DIR})