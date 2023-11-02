#ifndef ARROW_ARROW_H
#define ARROW_ARROW_H

#include "EventHandler.h"
#include "Shader.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Arrow {
public:
    Arrow();
    Arrow(EventHandler *eventHandler, float x, float y, float rotation, float scale);
    void move(float x, float y, float rotation, float scale, double duration);
    void onFrame();
    static void init();
private:

    struct Point {
        float x, y, rotation, scale;
    };
    const EventHandler *eventHandler;
    Point start;
    Point end;

    //Time
    double startTime;
    double duration;

    // Shader Program
    static unsigned int shaderProgram;
    static unsigned int VAO;
    //static unsigned int EBO;

    constexpr static float vertices[18] {
            0.000,	0.000,
            0.875,	0.566,
            0.625,	0.566,
            0.807,	0.427,
            0.693,	0.427,
            0.774,	1.011,
            0.693,	0.427,
            0.774,	1.011,
            0.726,	1.011
    };
};

#endif //ARROW_ARROW_H
