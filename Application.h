#ifndef ARROW_APPLICATION_H
#define ARROW_APPLICATION_H


#include "EventHandler.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Application {
public:
    explicit Application(GLFWwindow *window);

    EventHandler *getEventHandler();

    void exec(std::function<void()> func = nullptr);

    static int height;
    static int width;
    static float aspectRatio;
private:
    GLFWwindow *window;
    EventHandler eventHandler;
};


/*
 * int a = 0
 * while(true) {
 *  calc(a)
 * }
 * func calc() {
 *  calc()
 *  sdff
 * }
 */

#endif //ARROW_APPLICATION_H
