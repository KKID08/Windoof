#ifndef SHADER_H
#define SHADER_H


#include <string>
#include <iostream>
#include <fstream>
#include <GL/glew.h>

#include "DefaultShader.h"

class Shader {
public:
    static unsigned int loadShaderProgram(const std::string &folderPath) {
        unsigned int shaderProgram = glCreateProgram();

        // Load Shader
        unsigned int vertexShader = loadShader(shaderProgram, GL_VERTEX_SHADER, folderPath + "/vertex.glsl");
        unsigned int geometryShader = loadShader(shaderProgram, GL_GEOMETRY_SHADER, folderPath + "/geometry.glsl");
        unsigned int fragmentShader = loadShader(shaderProgram, GL_FRAGMENT_SHADER, folderPath + "/fragment.glsl");

        // Link Program
        glLinkProgram(shaderProgram);

        // Delete Shader
        /*
        glDeleteShader(vertexShader);
        glDeleteShader(geometryShader);
        glDeleteShader(fragmentShader);
        */

        // Check for shader program link errors
        int success;
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
            std::cerr << "Shader program linking error:\n" << infoLog << std::endl;
            return -1;
        }

        // Return
        return shaderProgram;
    };

private:
    inline static std::string readFile(const std::string &filename) {
        std::ifstream file(filename);
        std::string fileContent;
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                fileContent += line + "\n";
            }
            file.close();
        } else {
            return "";
        }
        return fileContent;
    }

    inline static int compileShader(const char *source, const unsigned int type, unsigned int &shaderID) {
        shaderID = glCreateShader(type);
        glShaderSource(shaderID, 1, &source, nullptr);
        glCompileShader(shaderID);
        // Check
        int success;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        return success;
    }

    inline static unsigned int loadShader(const unsigned int &shaderProgram, const unsigned int shaderType, const std::string &filePath) { // folderPath + "/vertex.glsl"
        std::string shaderCode = readFile(filePath);
        bool useDefaultShader = false;
        unsigned int shaderID = 0;
        while (shaderCode.empty() || !compileShader(shaderCode.c_str(), shaderType, shaderID)) {
            // Print Error
            if (useDefaultShader) {
                std::cerr << "Default Shader Error" << std::endl;
                exit(-1);
            } else if (!shaderCode.empty()) {
                char infoLog[512];
                glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
                std::cerr << "Shader compilation error:\n" << filePath << " " << infoLog << std::endl;
                glDeleteShader(shaderID);
            } else if (shaderType == GL_GEOMETRY_SHADER) {
                std::cout << "Geometry Shader at '" << filePath << "' not found" << std::endl;
            } else if (shaderType == GL_VERTEX_SHADER) {
                std::cerr << "Vertex Shader at '" << filePath << "' not found" << std::endl;
            } else if (shaderType == GL_FRAGMENT_SHADER) {
                std::cerr << "Fragment Shader at '" << filePath << "' not found" << std::endl;
            }

            // Try Default Shader
            useDefaultShader = true;
            switch (shaderType) {
                case GL_VERTEX_SHADER:
                    shaderCode = defaultVertexShader;
                    break;
                case GL_FRAGMENT_SHADER:
                    shaderCode = defaultFragmentShader;
                    break;
                default:
                    return -1;
            }
        }
        glAttachShader(shaderProgram, shaderID);
        return shaderID;
    }
};


#endif //SHADER_H
