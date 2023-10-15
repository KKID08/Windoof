#ifndef ARROW_ARROW_H
#define ARROW_ARROW_H

#include "EventHandler.h"

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
    static unsigned int EBO;
};

#endif //ARROW_ARROW_H
