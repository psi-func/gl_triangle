cmake_minimum_required(VERSION 3.16)
project(OpenGL_course)

find_package(OpenGL REQUIRED)

include_directories(external/glew-2.1.0/include)

add_executable(setup main.cpp)
target_link_libraries(setup PUBLIC glfw glew glm)

set(GLFW_BUILD_EXAMPLES OFF)
set(BUILD_SHARED_LIBS  ON)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)
set(GLFW_VULKAN_STATIC OFF)

add_subdirectory(external/glfw-3.3.7)
add_subdirectory(external/glew-2.1.0/build/cmake)
add_subdirectory(external/glm)