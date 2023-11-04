#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <csignal>

#include "Application.h"
#include "Arrow.h"
#include "Rectangle.h"

int main() {
    glfwInit();

    glfwWindowHint(GLFW_DECORATED, 0);
    glfwWindowHint(GLFW_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
    glfwWindowHint(GLFW_FOCUSED, GLFW_FALSE);
    glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);

    /*
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
     */

    int windowWidth, windowHeight;
    glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), nullptr, nullptr, &windowWidth, &windowHeight);

    GLFWwindow *window = glfwCreateWindow(windowWidth, windowHeight, "Translucent Background", nullptr, nullptr);
    if (!window) return -1;
    //glfwSetWindowPos(window, 0, 0);
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    Arrow::init();
    Rectangle::init();


    Application app(window);

    //int ac = 10;
    //Arrow **arrow = new Arrow*[ac];

    //for (int i = 0; i < ac; i++) {
    //    arrow[i] = new Arrow(app.getEventHandler(), 0, 0, 0, 1);
    //}

    Rectangle r(app.getEventHandler(), 0.2f, 0.2f, 0, 0, 0.4, 0, 0/*.7853982*/);
    Arrow arrow(app.getEventHandler(), 0.0, 0.0, -0.7853982, 0.1);

    //arrow_old.move(1, 1, 0.5, 1, 1);
    //Arrow arrow_old(app.getEventHandler(), 0, 0, 0.125, 0.5);
    //app.exec();

    //double *sleep = new double[ac];

    app.exec();

    /*app.exec([&arrow, sleep, ac]{
        for (int i = 0; i < ac; i++) {
            if (sleep[i] < glfwGetTime()) {
                double duration = ((double)rand()) / RAND_MAX * 10;
                sleep[i] = glfwGetTime() + duration;
                (*arrow[i]).move(((double)rand()) / RAND_MAX * 2 - 1, ((double)rand()) / RAND_MAX * 2 - 1, ((double)rand()) / RAND_MAX, ((double)rand()) / RAND_MAX / 10, duration);
            }
        }
    });*/
}