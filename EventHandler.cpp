#include <algorithm>
#include "EventHandler.h"

void EventHandler::listenOnFrame(std::function<void()> func/*void (*func)()*/) {
    frameListeners.push_back(func);
}

/*
void EventHandler::endListenOnFrame(std::function<void()> func) {//void (Arrow::*func)()) {
    auto it = std::find(frameListeners.begin(), frameListeners.end(), func);
    frameListeners.erase(it, it);
}
*/

void EventHandler::execFrame() {
    for (std::function<void()> func/*void (*func)()*/ : frameListeners) {
        func();
    }
}