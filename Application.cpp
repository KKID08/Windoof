#include "Application.h"

int Application::height;
int Application::width;
//float Application::aspectRatio;

Application::Application(GLFWwindow *window)
        : window(window) {
    glfwGetWindowSize(window, &width, &height);
    aspectRatio = (float) width / (float) height;
}

EventHandler *Application::getEventHandler() {
    return &eventHandler;
}

void Application::exec(std::function<void()> func) {
    while (!glfwWindowShouldClose(window)) {
        // Clear
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        if (func)
            func();
        eventHandler.execFrame();

        // Process Events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}