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
private:
    GLFWwindow* window;
    EventHandler eventHandler;
};


#endif //ARROW_APPLICATION_H
