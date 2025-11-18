#include "WinCtrl.h"
// a cambio de tener el poder, le da a core una ventana

GSC::WinCtrl::WinCtrl(){

    if (!glfwInit()) {
        GSC::log("|◉|X| Winctrl ERROR: glfw no init");
        return;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GSC::log("|◉|◉| Winctrl ok");
}

GSC::WinCtrl::~WinCtrl(){
    glfwDestroyWindow(corewindow);
    glfwTerminate();
}

void GSC::WinCtrl::initCoreWin(){

    corewindow = glfwCreateWindow(400, 400, "Core", nullptr, nullptr);
    if (!corewindow) {
        GSC::log("|◉|X| Winctrl ERROR: No se pudo crear la ventana");
        glfwTerminate();
        return;
    }
    
    glfwMakeContextCurrent(corewindow);

    GSC::log("|◉|◉| Win has glfwWin ok");
}

GLFWwindow* GSC::WinCtrl::getCoreWin(){
    return corewindow;
}


void GSC::WinCtrl::clearWindow(){
    
    glClearColor(0.1f, 0.4f, 0.55f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    GSC::log("|◉|◉| Win cleared ok");
    
}

void GSC::WinCtrl::pollWindow(){
    glfwPollEvents();   // leer teclado, mouse, lógica de ventana
    glfwSwapBuffers(corewindow);  // mostrar el frame en pantalla
    GSC::log("|◉|◉| Win polled ok");

}