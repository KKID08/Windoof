#ifndef SHADER_H
#define SHADER_H


#include <string>
#include <iostream>
#include <fstream>
#include <GL/glew.h>

#include "DefaultShader.h"

class Shader {
public:
    static unsigned int loadShaderProgram(std::string folderPath) {
        std::string vertexShaderS = readFile(folderPath + "/vertex.glsl");
        std::string geometryShaderS = readFile(folderPath + "/geometry.glsl");
        std::string fragmentShaderS = readFile(folderPath + "/fragment.glsl");

        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

        GLuint geometryShader;
        if (!geometryShaderS.empty())
            geometryShader = glCreateShader(GL_GEOMETRY_SHADER);

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        GLuint shaderProgram = glCreateProgram();

        // Load Shader
        unsigned int vertexShader   = loadShader(shaderProgram, GL_VERTEX_SHADER, folderPath + "/vertex.glsl");
        unsigned int geometryShader = loadShader(shaderProgram, GL_GEOMETRY_SHADER, folderPath + "/geometry.glsl");
        unsigned int fragmentShader = loadShader(shaderProgram, GL_FRAGMENT_SHADER, folderPath + "/fragment.glsl");

        // Link Program
        glLinkProgram(shaderProgram);

        return shaderProgram;
    };

private:
    static std::string readFile(std::string  filename) {
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
};


#endif //SHADER_H
