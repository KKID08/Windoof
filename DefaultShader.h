#ifndef DEFAULTSHADER_H
#define DEFAULTSHADER_H

const char* defaultVertexShader = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;

    void main() {
        gl_Position = vec4(aPos, 1.0);
    }
)";
const char* defaultFragmentShader = R"(
    #version 330 core
    out vec4 FragColor;

    void main() {
        float squareSize = 0.05;
        vec2 fragCoord = gl_FragCoord.xy / 800.0;
        int squareX = int(fragCoord.x / squareSize);
        int squareY = int(fragCoord.y / squareSize);
        bool isBlack = (squareX + squareY) % 2 == 0;
        vec3 color = isBlack ? vec3(0.0, 0.0, 0.0) : vec3(0.5, 0.0, 0.5);
        FragColor = vec4(color, 1.0);
    }
)";

#endif //DEFAULTSHADER_H
