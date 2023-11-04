#ifndef RECTANGLE_H
#define RECTANGLE_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Application.h"
#include "EventHandler.h"
#include "Shader.h"

class Rectangle {
public:
    Rectangle(EventHandler *eventHandler, float width, float height, float centerX, float centerY, float outlineScale = 0, float smoothness = 0, float rotation = 0);

    void move(double duration, float width, float height, float centerX, float centerY, float outlineScale = 0, float smoothness = 0, float rotation = 0);

    void onFrame();

    static void init();

private:
    struct {
        float width;
        float height;
        float centerX;
        float centerY;
        float smoothness;
        float rotation;
        float outlineScale;
    } m_start, m_end;

    double m_startTime;
    double m_duration;

    static unsigned int shaderProgram;
    static unsigned int VAO;
    /*
    constexpr static float m_vertices[12] {
        -1, -1,
         1,  1,
         1, -1,
        -1, -1,
         1,  1,
        -1,  1
    };
    */
    constexpr static float m_vertices[2] {
            0.00, 0.00,
    };
};


#endif //RECTANGLE_H
