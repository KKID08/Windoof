#ifndef ARROW_EVENTHANDLER_H
#define ARROW_EVENTHANDLER_H

#include <vector>
#include <functional>

class EventHandler {
public:
    void listenOnFrame(std::function<void()> func);//void (*func)());
    //void endListenOnFrame(std::function<void()> func);//void (*func)());
    void execFrame();
private:
    std::vector<std::function<void()>> frameListeners;//void (*)()> frameListeners;
};


#endif //ARROW_EVENTHANDLER_H