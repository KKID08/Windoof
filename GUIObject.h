#ifndef GUIOBJEKT_H
#define GUIOBJEKT_H

#include <iostream>

struct ShaderCollection {
    const char* vertexShader;
    const char* tesselationShader;
    const char* geometryShader;
    const char* fragmentShader;
};

class GUIObject {
protected:
    inline virtual ShaderCollection getShader(){
        return {nullptr, nullptr, nullptr};
    };

    int a = 0;
};

class Pfeil : GUIObject {
public:
    void test() {
        std::cout << a;
    }

    inline ShaderCollection getShader() override {
        return shaderCollection;
    }

    static int a;
private:
    static ShaderCollection shaderCollection;
};

#endif //GUIOBJEKT_H
