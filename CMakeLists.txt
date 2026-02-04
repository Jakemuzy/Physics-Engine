cmake_minimum_required(VERSION 3.5)
project(Physics-Engine C)

find_package(OpenGL REQUIRED)

# Disable uncessary glfw build settings 

set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "")
set(GLFW_INSTALL OFF CACHE INTERNAL "")

add_subdirectory(dependencies/glfw)

# Add srcs files

file(GLOB ENGINE_SOURCES "src/*.c")
add_executable(Physics-Engine ${ENGINE_SOURCES})

# Glad library

add_library(glad STATIC dependencies/glad/src/glad.c)
target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glad/
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glad/KHR
)

# Add header files

target_include_directories(Physics-Engine 
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(Physics-Engine 
    PRIVATE glfw
    PRIVATE glad
    PRIVATE OpenGL::GL
)

