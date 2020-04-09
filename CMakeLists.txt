cmake_minimum_required(VERSION 3.16)

project(pong VERSION 0.1)

set(SOURCE_FILES
    src/main.cpp
    src/Shader.cpp
    src/Renderer.cpp
    src/VertexBuffer.cpp
    src/IndexBuffer.cpp
    src/VertexArray.cpp
    src/GameObject.cpp
    src/Paddle.cpp
    src/Ball.cpp
    src/Random.cpp
    src/Game.cpp
    src/Time.cpp
)

add_executable(pong ${SOURCE_FILES})
target_compile_features(pong PUBLIC cxx_std_17)

# Sets the opengl version to use.
set(OPENGL_VERSION_MAJOR 4)
set(OPENGL_VERSION_MINOR 6)
set(OPENGL_VERSION_PROFILE "core") #"core" or "compatibility"

target_compile_definitions(pong
    PUBLIC OPENGL_VERSION_MAJOR=${OPENGL_VERSION_MAJOR}
    PUBLIC OPENGL_VERSION_MINOR=${OPENGL_VERSION_MINOR}
    PUBLIC OPENGL_VERSION_PROFILE=${OPENGL_VERSION_PROFILE}
)

# copy res to bin directory
# Create a target that will run cmake with the CopyFile.cmake script everytime we build.
set(RESOURCE_DIR_IN "${CMAKE_CURRENT_SOURCE_DIR}/res")
set(RESOURCE_DIR_OUT "${CMAKE_CURRENT_BINARY_DIR}")
set(COPY_FILE_SCRIPT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CopyFile.cmake")

add_custom_target(
    copy_res_dir
    ${CMAKE_COMMAND}
    -DSOURCE_FILE=${RESOURCE_DIR_IN}
    -DDESTINATION_FILE=${RESOURCE_DIR_OUT} 
    -P ${COPY_FILE_SCRIPT_PATH}
    VERBATIM 
)

add_dependencies( pong copy_res_dir )

#glm
add_subdirectory(lib/glm)
target_link_libraries(pong PUBLIC glm)

# glfw
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory(lib/glfw)
target_link_libraries(pong PUBLIC glfw)


#glad
set(GLAD_PROFILE ${OPENGL_VERSION_PROFILE} CACHE STRING "OpenGL Profile to use. compatibility/core" FORCE)
set(GLAD_API "gl=${OPENGL_VERSION_MAJOR}.${OPENGL_VERSION_MINOR}" CACHE STRING "OpenGL Version to use. example usage: gl=3.3" FORCE)
add_subdirectory(lib/glad)
target_include_directories(pong PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/lib/glad/include")
target_link_libraries(pong PUBLIC glad)
