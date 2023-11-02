#ifndef SHADER_H
#define SHADER_H


#include <string>
#include <iostream>
#include <fstream>
#include <GL/glew.h>

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

        // Vertex shader
        const char* vsc = vertexShaderS.c_str();
        glShaderSource(vertexShader, 1, &vsc, nullptr);
        glCompileShader(vertexShader);
        glAttachShader(shaderProgram, vertexShader);

        // Geometry shader
        const char* gsc = geometryShaderS.c_str();
        if (!geometryShaderS.empty()) {
            glShaderSource(geometryShader, 1, &gsc, nullptr);
            glCompileShader(geometryShader);
            glAttachShader(shaderProgram, geometryShader);
        }

        // Fragment shader
        const char* fsc = fragmentShaderS.c_str();
        glShaderSource(fragmentShader, 1, &fsc, nullptr);
        glCompileShader(fragmentShader);
        glAttachShader(shaderProgram, fragmentShader);

        glLinkProgram(shaderProgram);

        // Check for shader program link errors
        GLint success;
        GLchar infoLog[512];
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
            std::cerr << "Shader program linking error: " << infoLog << std::endl;
        }

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
