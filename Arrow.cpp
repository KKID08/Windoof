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
    glUniform1f(glGetUniformLocation(shaderProgram, "start.x"), start.x);
    glUniform1f(glGetUniformLocation(shaderProgram, "start.y"), start.y);
    glUniform1f(glGetUniformLocation(shaderProgram, "start.rotation"), start.rotation);
    glUniform1f(glGetUniformLocation(shaderProgram, "start.scale"), start.scale);
    glUniform1f(glGetUniformLocation(shaderProgram, "end.x"), end.x);
    glUniform1f(glGetUniformLocation(shaderProgram, "end.y"), end.y);
    glUniform1f(glGetUniformLocation(shaderProgram, "end.rotation"), end.rotation);
    glUniform1f(glGetUniformLocation(shaderProgram, "end.scale"), end.scale);
    glUniform1d(glGetUniformLocation(shaderProgram, "startTime"), startTime);
    glUniform1d(glGetUniformLocation(shaderProgram, "duration"), duration);
    glUniform1d(glGetUniformLocation(shaderProgram, "currentTime"), currentTime);
    glUniform1f(glGetUniformLocation(shaderProgram, "currentTimeColor"), currentTime);

    // Use the shaders program
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
    shaderProgram = Shader::loadShaderProgram("../resources/shaders/arrow"); // TODO: Change Later

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