cmake_minimum_required(VERSION 3.0)
project(Arrow)

# Set the paths to the libraries and include directories
set(GLFW_PATH "/home/sean/libs/glfw")
set(OPENGL_INCLUDE_DIRS "/home/sean/libs/glfw/src")
set(GLEW_PATH "/home/sean/libs/glew")

# Find OpenGL
find_package(OpenGL REQUIRED)

# Source files
set(SOURCES main.cpp ${GLEW_PATH}/src/glew.c ${GLEW_PATH}/include/GL/glew.h
        Arrow.h Arrow.cpp
        EventHandler.h EventHandler.cpp
        Application.h Application.cpp
        Rectangle.h Rectangle.cpp
        DefaultShader.h Shader.h
)

# Add the GLAD source files directly
#add_library(glad ${GLAD_PATH}/src/glad.c)

# Create the executable
add_executable(Arrow ${SOURCES})

# Link GLFW, OpenGL, and GLAD
target_include_directories(Arrow PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${GLEW_PATH}/include ${GLFW_PATH}/include ${OPENGL_INCLUDE_DIRS})
target_link_libraries(Arrow PRIVATE ${GLFW_PATH}/build/src/libglfw3.a ${GLEW_PATH}/lib/libGLEW.a ${OPENGL_LIBRARIES})