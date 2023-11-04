#include "Rectangle.h"

unsigned int Rectangle::shaderProgram;
unsigned int Rectangle::VAO;
//float Application::aspectRatio;

Rectangle::Rectangle(EventHandler *eventHandler, float width, float height, float centerX, float centerY, float outlineScale, float smoothness, float rotation) :
        m_start({0, 0, 0, 0, 0, 0}),
        m_end({width, height, centerX, centerY, smoothness, rotation, outlineScale}),
        m_startTime(0), m_duration(0) {
    eventHandler->listenOnFrame([this] { onFrame(); });
}

void Rectangle::move(double duration, float width, float height, float centerX, float centerY, float outlineScale, float smoothness, float rotation) {
    m_start = m_end;
    m_duration = duration;
    m_startTime = glfwGetTime();
    m_end = {width, height, centerX, centerY, smoothness, rotation};
}

void Rectangle::onFrame() {
    glUseProgram(shaderProgram);

    glUniform1f(glGetUniformLocation(shaderProgram, "start.width"), m_start.width);
    glUniform1f(glGetUniformLocation(shaderProgram, "start.height"), m_start.height);
    glUniform1f(glGetUniformLocation(shaderProgram, "start.centerX"), m_start.centerX);
    glUniform1f(glGetUniformLocation(shaderProgram, "start.centerY"), m_start.centerY);
    glUniform1f(glGetUniformLocation(shaderProgram, "start.outlineScale"), m_start.outlineScale);
    glUniform1f(glGetUniformLocation(shaderProgram, "start.smoothness"), m_start.smoothness);
    glUniform1f(glGetUniformLocation(shaderProgram, "start.rotation"), m_start.rotation);
    glUniform1f(glGetUniformLocation(shaderProgram, "end.width"), m_end.width);
    glUniform1f(glGetUniformLocation(shaderProgram, "end.height"), m_end.height);
    glUniform1f(glGetUniformLocation(shaderProgram, "end.centerX"), m_end.centerX);
    glUniform1f(glGetUniformLocation(shaderProgram, "end.centerY"), m_end.centerY);
    glUniform1f(glGetUniformLocation(shaderProgram, "end.outlineScale"), m_end.outlineScale);
    glUniform1f(glGetUniformLocation(shaderProgram, "end.smoothness"), m_end.smoothness);
    glUniform1f(glGetUniformLocation(shaderProgram, "end.rotation"), m_end.rotation);

    glUniform1d(glGetUniformLocation(shaderProgram, "startTime"), m_startTime);
    glUniform1d(glGetUniformLocation(shaderProgram, "duration"), m_duration);
    glUniform1d(glGetUniformLocation(shaderProgram, "currentTime"), glfwGetTime());

    glUniform1f(glGetUniformLocation(shaderProgram, "aspectRatio"), Application::aspectRatio);

    //    float width;
    //    float height;
    //    float centerX;
    //    float centerY;
    //    float smoothness;
    //    float rotation;

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 1);
}

void Rectangle::init() {
    // Shader
    shaderProgram = Shader::loadShaderProgram("../resources/shader/rectangle"); // TODO: Change later

    unsigned int VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    // 1. bind Vertex Array Object
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 2. copy our vertices array in a buffer for OpenGL to use
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);
    // 3. then set our vertex attributes pointers
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
}