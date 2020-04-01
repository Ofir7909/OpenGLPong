cmake_minimum_required(VERSION 3.16)

project(pong VERSION 0.1)

set(SOURCE_FILES
    src/main.cpp
    src/Shader.cpp
)

add_executable(pong ${SOURCE_FILES})

# glfw
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
target_link_libraries(pong PUBLIC glfw)


#glad
add_subdirectory(lib/glad)
# add_library("glad" "${GLAD_DIR}/src/glad.c")
target_include_directories(pong PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/lib/glad/include")
target_link_libraries(pong PUBLIC glad)
