
#include "Core.h"

#include <GLFW/glfw3.h>


GSC::Core::Core()
{
    lgc = std::make_unique<LgcCtrl>();
    win = std::make_unique<WinCtrl>();
    gpu = std::make_unique<GPUCtrl>();   
}
GSC::Core::~Core(){}

void GSC::Core::GO(){


    GSC::log("  Core: Hello :)");

    
    if (!glfwInit()) {
        log("Error: glfwInit falló");
        return;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Motor Crudo", nullptr, nullptr);
    if (!window) {
        log("Error: no se pudo crear la ventana");
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    
    /*
        2. Inicializar GLAD (cargar punteros OpenGL)
    */
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        log("Error: GLAD no pudo cargarse");
        return;
    }


        /*
        3. Crear un shader mínimo
    */


    const char* ver_src = gpu->getShader(0);

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &ver_src, nullptr);
    glCompileShader(vs);

    const char* fra_src = gpu->getShader(0);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fra_src, nullptr);
    glCompileShader(fs);

    GLuint shader = glCreateProgram();
    glAttachShader(shader, vs);
    glAttachShader(shader, fs);
    glLinkProgram(shader);

    glDeleteShader(vs);
    glDeleteShader(fs);




    /*
        4. Crear un VAO-VBO con un triángulo
    */

    float tri[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tri), tri, GL_STATIC_DRAW);

    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE,
        3 * sizeof(float), (void*)0
    );
    glEnableVertexAttribArray(0);

    /*
        5. Loop principal
    */
    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
    }

    /*
        6. Cleanup crudo
    */

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shader);

    glfwDestroyWindow(window);
    glfwTerminate();

    log("Core: bye :)");

}

