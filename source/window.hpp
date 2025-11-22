#pragma once
#include <glad/glad.h>  
#include <GLFW/glfw3.h> 

struct Window {
    GLFWwindow* win;
    bool mouse_is_on = true;
    Window(int w, int h, const char* title, int interval) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        win = glfwCreateWindow(w, h, title, nullptr, nullptr);
        glfwMakeContextCurrent(win);
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        glEnable(GL_DEPTH_TEST);
        glfwSwapInterval(interval);
    }

    ~Window(){
        glfwDestroyWindow(win);
        glfwTerminate();
    }

    bool shouldClose() { return glfwWindowShouldClose(win); }
    void close()       {glfwSetWindowShouldClose(win, GLFW_TRUE); }
    void poll()        { glfwPollEvents(); }
    void swap()        { glfwSwapBuffers(win); }
    void mouse_mode()  {mouse_is_on = !mouse_is_on;}
};