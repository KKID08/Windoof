#include <iostream>
#include "Arrow.h"


unsigned int Arrow::shaderProgram;
unsigned int Arrow::VAO;

Arrow::Arrow() {}

Arrow::Arrow(EventHandler *eventHandler, const float x, const float y, const float rotation, const float scale)
: eventHandler(eventHandler), start(), end({x, y, rotation, scale})
{
    eventHandler->listenOnFrame([this]{onFrame();});
}

void Arrow::onFrame() {
    glUseProgram(shaderProgram);
    double currentTime = glfwGetTime();
    //std::cout << ((duration == 0) ? 1 : (currentTime - startTime) / duration) << " " << start.rotation << " "  << end.rotation << std::endl;
    // Set Uniforms
    glUniform1f(glGetUniformLocation(shaderProgram, "start.x"), start.x);
    glUniform1f(glGetUniformLocation(shaderProgram, "start.y"), start.y);
    glUniform1f(glGetUniformLocation(shaderProgram, "start.rotation"), start.rotation);
    glUniform1f(glGetUniformLocation(shaderProgram, "start.scale"), start.scale);
    //if (start.timestamp == -1) glUniform1d(glGetUniformLocation(shaderProgram, "start.timestamp"), currentTime);
    //else                       glUniform1d(glGetUniformLocation(shaderProgram, "start.timestamp"), start.timestamp);
    glUniform1f(glGetUniformLocation(shaderProgram, "end.x"), end.x);
    glUniform1f(glGetUniformLocation(shaderProgram, "end.y"), end.y);
    glUniform1f(glGetUniformLocation(shaderProgram, "end.rotation"), end.rotation);
    glUniform1f(glGetUniformLocation(shaderProgram, "end.scale"), end.scale);
    //glUniform1d(glGetUniformLocation(shaderProgram, "end.timestamp"), end.timestamp);
    glUniform1d(glGetUniformLocation(shaderProgram, "startTime"), startTime);
    glUniform1d(glGetUniformLocation(shaderProgram, "duration"), duration);
    glUniform1d(glGetUniformLocation(shaderProgram, "currentTime"), currentTime);
    glUniform1f(glGetUniformLocation(shaderProgram, "currentTimeColor"), currentTime);

    // Use the shader program
    glUseProgram(shaderProgram);

    // Bind the VAO and draw the triangle
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 9);
}

void Arrow::move(float x, float y, float rotation, float scale, double duration) {
    this->start = end;
    this->end = {x, y, rotation, scale};
    this->startTime = glfwGetTime();
    this->duration = duration;
}

void Arrow::init() {

    // Angle, Distance // Angle starts horisontal right and turn left
    /*static const float vertices[18] {

            // Pointer
            0.0f, 0.0f, // Pointer 0
            0.875f, 0.354f, // Pointer Right 1
            0.625f, 0.354f, // Pointer Left 2

             // Right Stem
            0.821f, 0.277f, // Middle Right 3
            0.679f, 0.277f, // Middle Left 4
            0.769f, 1.007f, // Bottom Right 5
            // Left Stem
            0.679f, 0.277f, // Middle Left 4
            0.769f, 1.007f, // Bottom Right 5
            0.731f, 1.007f, // Bottom Left 6

    };
    */
    static const float vertices[18] {
            0,	0,
            0.875,	0.566,
            0.625,	0.566,
            0.807,	0.427,
            0.693,	0.427,
            0.774,	1.011,
            0.693,	0.427,
            0.774,	1.011,
            0.726,	1.011
    };

    /*
    // Create and bind a VAO and VBO for the triangle
    unsigned int VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Configure vertex attributes
    glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*) sizeof(float));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

     */
    const char *vertexShaderSource = R"(
        #version 400 core
        #define M_PI 3.1415926535897932384626433832795

        layout(location = 0) in float angle;
        layout(location = 1) in float distance;
        layout(location = 2) in float counter;

        struct Point {
            float x, y, rotation, scale;
        };

        uniform Point start;
        uniform Point end;
        uniform double startTime;
        uniform double duration;
        uniform double currentTime;

        void main() {
            float progress = duration == 0 ? 1 : float(clamp((currentTime - startTime) / duration, 0, 1));
            vec2 arrowPos = vec2(
                mix(start.x, end.x, progress),
                mix(start.y, end.y, progress)
            );
            float pScale = mix(start.scale, end.scale, progress);
            float pRotation = mix(start.rotation, end.rotation, progress);


            // Calc Point
            float angleTemp = (angle + pRotation);
            float newAngle = angleTemp - trunc(angleTemp);
            float newDistance = distance * pScale;
            vec2 newPos = vec2(
                newDistance * cos(newAngle * 360 * M_PI/180), // 2 = 360 / 180
                newDistance * sin(newAngle * 360 * M_PI/180)
            );
            //gl_Position = vec4((arrowPos + newPos), 0.0f, 1.0f); // New Position
            //gl_Position = vec4((newPos.x), (newPos.y + angle), 0.0f, 1.0f); // New Position
            //gl_Position = vec4(counter, newPos.y, 0.0, 1.0);
            gl_Position = vec4(arrowPos + newPos, 0.0, 1.0);
            //gl_Position = vec4(distance - 1, (angle) - 1, 0.0, 1.0);
        }
    )";

    const char *fragmentShaderSource = R"(
        #version 330 core
        in vec4 gl_FragCoord;
        out vec4 FragColor;
        uniform float currentTimeColor;
        void main() {
            FragColor = vec4(pow(sin(currentTimeColor / 2 ), 2), pow(cos(currentTimeColor / 2), 2), 0.2f, 0.8f); // Orange color with transparency
        }
    )";
    /*
    // Create and compile the vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // Check for vertex shader compilation errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "Vertex shader compilation failed: " << infoLog << std::endl;
    }

    // Create and compile the fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // Check for fragment shader compilation errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "Fragment shader compilation failed: " << infoLog << std::endl;
    }

    // Create and link the shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for program linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Shader program linking failed: " << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //glUseProgram(shaderProgram);
    */

    // Create and compile the vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "Vertex shader compilation failed: " << infoLog << std::endl;
    }

    // Create and compile the fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Check for fragment shader compilation errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "Fragment shader compilation failed: " << infoLog << std::endl;
    }

    // Create and link the shader program
    //unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Define triangle vertices
    /*float vertices[] = {
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.0f,  0.5f
    };*/

    // Define the order of vertices with an EBO
    /*unsigned int indices[] = {
            0, 1, 2
    };*/

    // Create and bind a VAO and VBO for the triangle
    unsigned int VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Configure vertex attributes
    glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)sizeof(float));
    glEnableVertexAttribArray(1);
}

/*
 * #version 400 core
        #define M_PI 3.1415926535897932384626433832795

        layout (location = 0) in float distance;
        layout (location = 1) in float angle;

        struct Point {
            float x, y, rotation, scale;
            double timestamp;
        };

        uniform Point start;
        uniform Point end;
        uniform double currentTime;

        out vec4 gl_Position;

        void main() {
            // Calc Arrow Position
            float progress = float((currentTime - start.timestamp) / (end.timestamp - start.timestamp));
            vec2 arrowPos = vec2(
                mix(start.x, end.x, progress),
                mix(start.y, end.y, progress)
            );
            float pScale = mix(start.scale, end.scale, progress);
            float pRotation = mix(start.rotation, end.rotation, progress);

            // Calc Point
            float angleTemp = (angle + pRotation);
            float newAngle = angleTemp - floor(angleTemp);
            float newDistance = distance * pScale;
            vec2 newPos = vec2(
                newDistance * cos(M_PI * newAngle * 2.0f), // 2 = 360 / 180
                newDistance * sin(M_PI * newAngle * 2.0f)
            );
            gl_Position = vec4(arrowPos + newPos, 0.0f, 1.0f); // New Position
        }
 */