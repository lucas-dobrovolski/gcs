#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "../gsc.h"

namespace GSC {

class WinCtrl { 
    
    private:

        GLFWwindow* corewindow;

    public:

        WinCtrl();

        ~WinCtrl();

        void initCoreWin();    
        GLFWwindow* getCoreWin();

        void clearWindow();
        void pollWindow();


};

/*
class Window { public:
    Window(int w, int h, const std::string& t, bool vsync = true);
    ~Window();

    int getWidth() const; 
    int getHeight() const;
    bool getShouldLive() const;

    void swapBuffers();
    void pollEvents();
};
*/






}