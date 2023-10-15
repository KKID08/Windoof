#include "Application.h"

Application::Application(GLFWwindow *window)
: window(window)
{

}

EventHandler *Application::getEventHandler() {
    return &eventHandler;
}

void Application::exec(std::function<void()> func) {
    while (true) {//!glfwWindowShouldClose(window)) {
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