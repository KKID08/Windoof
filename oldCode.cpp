#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Vertex and Fragment shader source code
const char* vertexShaderSource = R"(
    #version 330 core
    layout(location = 0) in vec2 aPos;
    void main() {
        gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    void main() {
        FragColor = vec4(1.0f, 0.5f, 0.2f, 0.5f); // Orange color with transparency
    }
)";

int main() {
    glfwInit();

    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

    int windowWidth, windowHeight;
    glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), nullptr, nullptr, &windowWidth, &windowHeight);

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Translucent Background", nullptr, nullptr);
    if (!window) return -1;
    glfwSetWindowPos(window, 0, 0);
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Create and compile the vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Create and compile the fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Create and link the shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Define triangle vertices
    float vertices[] = {
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.0f,  0.5f
    };

    // Define the order of vertices with an EBO
    unsigned int indices[] = {
            0, 1, 2
    };

    // Create and bind a VAO and VBO for the triangle
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Configure vertex attributes
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);


    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        // Use the shader program
        glUseProgram(shaderProgram);

        // Bind the VAO and draw the triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap the buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}
