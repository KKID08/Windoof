cmake_minimum_required(VERSION 3.0)
project(OpenGL)

# Set the paths to the libraries and include directories
set(GLFW_PATH "C:/Users/domin/Documents/Private/Coding/OpenGL/Libs/glfw")
set(OPENGL_INCLUDE_DIRS "C:/Users/domin/Documents/Private/Coding/OpenGL/Libs/glfw/src")
set(GLEW_PATH "C:/Users/domin/Documents/Private/Coding/OpenGL/Libs/glew")

# Find OpenGL
find_package(OpenGL REQUIRED)

# Source files
set(SOURCES main.cpp
        Arrow.h Arrow.cpp
        EventHandler.h EventHandler.cpp
        Application.h Application.cpp
        GUIObject.cpp
        GUIObject.h
        Shader.h
        DefaultShader.h
)

# Add the GLAD source files directly
#add_library(glad ${GLAD_PATH}/src/glad.c)

# Create the executable
add_executable(OpenGL ${SOURCES})

# Link GLFW, OpenGL, and GLAD
target_include_directories(OpenGL PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${GLEW_PATH}/include ${GLFW_PATH}/include ${OPENGL_INCLUDE_DIRS})
target_link_libraries(OpenGL PRIVATE ${GLFW_PATH}/lib/glfw3.lib ${GLEW_PATH}/lib/Release/x64/glew32.lib ${OPENGL_LIBRARIES})