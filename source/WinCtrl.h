#pragma once

namespace GSC {

class WinCtrl { 
    
    public:

        WinCtrl();

        ~WinCtrl();

        void init();    

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