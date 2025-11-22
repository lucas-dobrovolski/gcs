#include <iostream>
#include <vector>   
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <glad/glad.h>  
#include <GLFW/glfw3.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


/////////////////////////////////////////////////////////////////////////////////// DEF STRUCT Vertex
struct Vertex {
    glm::vec3 position;   // 3 floats
    glm::vec3 normal;     // 3 floats
    glm::vec2 uv;         // 2 floats
};
/////////////////////////////////////////////////////////////////////////////////// DEF STRUCT Window
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
/////////////////////////////////////////////////////////////////////////////////// DEF logmsg
void logmsg(const char* msg){
    std::cout << " ◉ " << msg << "\n";
}
/////////////////////////////////////////////////////////////////////////////////// DEF framebuffer_size_callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // OpenGL actualiza su viewport al nuevo tamaño
    glViewport(0, 0, width, height);
}
/////////////////////////////////////////////////////////////////////////////////// DEF readFile
std::string readFile(const char* path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        logmsg("ERROR: READ FILE");
        std::cerr << "No pude abrir " << path << "\n";
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
/////////////////////////////////////////////////////////////////////////////////// DEF COMPILE SHADER
GLuint compileShader(const char* path, GLenum type) {
    std::string src = readFile(path);
    if (src.empty()) return 0;

    GLuint shader = glCreateShader(type);
    const char* csrc = src.c_str();

    glShaderSource(shader, 1, &csrc, nullptr);
    glCompileShader(shader);

    GLint ok;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);

    if (!ok) {
        GLint len;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

        std::string log(len, '\0');
        glGetShaderInfoLog(shader, len, nullptr, &log[0]);
        logmsg("ERROR: COMPILE SHADER");
        std::cerr << "Error compilando " << path << ":\n"
                  << log << "\n";

        glDeleteShader(shader);
        return 0;
    }

    return shader;
}
/////////////////////////////////////////////////////////////////////////////////// DEF LINK SHADER
GLuint makeProgram(const char* vpath, const char* fpath) {
    GLuint vs = compileShader(vpath, GL_VERTEX_SHADER);
    GLuint fs = compileShader(fpath, GL_FRAGMENT_SHADER);

    if (!vs || !fs) {
        logmsg("ERROR: MAKE PROGRAM");
        std::cerr << "No se pudieron compilar los shaders\n";
        return 0;
    }

    GLuint prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, fs);
    glLinkProgram(prog);

    GLint ok;
    glGetProgramiv(prog, GL_LINK_STATUS, &ok);

    if (!ok) {
        GLint len;
        glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);

        std::string log(len, '\0');
        glGetProgramInfoLog(prog, len, nullptr, &log[0]);
        logmsg("ERROR: MAKE PROGRAM");
        std::cerr << "Error linkeando programa:\n"
                  << log << "\n";

        glDeleteProgram(prog);
        prog = 0;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    return prog;
}
/////////////////////////////////////////////////////////////////////////////////// DEF CLASS VAO
class VAO {
private:
    GLuint ID;
    GLuint VBO = 0;
    GLuint EBO = 0;

public:
    VAO() {
        glGenVertexArrays(1, &ID);
        glBindVertexArray(ID);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    }

    ~VAO() {
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        glDeleteVertexArrays(1, &ID);
    }

    void bind() const { glBindVertexArray(ID); }
    void unbind() const { glBindVertexArray(0); }

    void setVertexData(const std::vector<Vertex>& vec, GLenum usage = GL_STATIC_DRAW) {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vec.size() * sizeof(Vertex), vec.data(), usage);
    }

    void setIndexData(const std::vector<unsigned int>& vec, GLenum usage = GL_STATIC_DRAW) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, vec.size() * sizeof(unsigned int), vec.data(), usage);
    }

    void addAttrib(GLuint index, GLint size, GLenum type, GLboolean normalized,
                   GLsizei stride, const void* offset) const {
                       /* Agrega un atributo de vertice. 
                       index:       ubicacion del atrib en shader: 0, 1, 2...
                       size:        cantidad de componentes (3 para vec3, 2 para vec2)
                       type:        tipo de dato (GL_FLOAT, etc.)
                       normalized:  si los datos deben normalizarse
                       stride:      tamaño total del vértice (sizeof(Vertex))
                       offset:      desplazamiento dentro del vértice xej " (offsetof(Vertex, normal)) ""*/
                       glEnableVertexAttribArray(index);
                       glVertexAttribPointer(index, size, type, normalized, stride, offset);
    }
};

/////////////////////////////////////////////////////////////////////////////////// def CAMERA
struct Camera {
    glm::vec3 pos    = glm::vec3(3.0f, 3.0f, 3.0f);
    float yaw        = -135.0f;   // apunta al origen desde la diagonal
    float pitch      = -20.0f;

    float speed      = 3.0f;
    float sens       = 0.1f;

    glm::vec3 front  = glm::vec3(0,0,-1);
    glm::vec3 up     = glm::vec3(0,1,0);
    glm::vec3 rightv = glm::vec3(1,0,0);

    void updateVectors() {
        float cy = glm::radians(yaw);
        float cp = glm::radians(pitch);

        glm::vec3 f;
        f.x = cos(cp) * cos(cy);
        f.y = sin(cp);
        f.z = cos(cp) * sin(cy);

        front  = glm::normalize(f);
        rightv = glm::normalize(glm::cross(front, glm::vec3(0,1,0)));
        up     = glm::normalize(glm::cross(rightv, front));
    }

    glm::mat4 getView() const {
        return glm::lookAt(pos, pos + front, up);
    }
};

Camera* gCam = nullptr;

void mouse_callback(GLFWwindow*, double xpos, double ypos) {
    static bool first = true;
    static double lastx, lasty;

    if (first) {
        lastx = xpos; 
        lasty = ypos;
        first = false;
    }

    double dx = xpos - lastx;
    double dy = lasty - ypos;

    lastx = xpos;
    lasty = ypos;

    gCam->yaw   += dx * gCam->sens;
    gCam->pitch += dy * gCam->sens;

    if (gCam->pitch > 89.0f) gCam->pitch = 89.0f;
    if (gCam->pitch < -89.0f) gCam->pitch = -89.0f;

    gCam->updateVectors();
}


/////////////////////////////////////////////////////////////////////////////////// MAIN


int main(){
    /////////////////////////////////////////////////////////////////////////////////// MAIN - GLFW INIT
    Window window(800, 600, "GCS", 1);
    glfwSetFramebufferSizeCallback(window.win, framebuffer_size_callback);
    /////////////////////////////////////////////////////////////////////////////////// MAIN - CUBO-> VERTICES E INDICES
    float s = 1.0f;
    std::vector<Vertex> vertices = {
        // front face (+z)
        {{-s,-s, s},{0,0,1},{0,0}},
        {{ s,-s, s},{0,0,1},{1,0}},
        {{ s, s, s},{0,0,1},{1,1}},
        {{-s, s, s},{0,0,1},{0,1}},
        // back face (-z)
        {{-s,-s,-s},{0,0,-1},{1,0}},
        {{ s,-s,-s},{0,0,-1},{0,0}},
        {{ s, s,-s},{0,0,-1},{0,1}},
        {{-s, s,-s},{0,0,-1},{1,1}}
    };
    std::vector<unsigned int> indices = {
        0,1,2, 2,3,0,    // front
        4,5,6, 6,7,4,    // back
        4,0,3, 3,7,4,    // left
        1,5,6, 6,2,1,    // right
        3,2,6, 6,7,3,    // top
        4,5,1, 1,0,4     // bottom
    };
    /////////////////////////////////////////////////////////////////////////////////// MAIN - CREATE BUFFERS
    VAO vao;
    vao.bind();

    vao.setVertexData(vertices);
    vao.setIndexData(indices);

    vao.addAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    vao.addAttrib(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    vao.addAttrib(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

    vao.unbind();
    /////////////////////////////////////////////////////////////////////////////////// MAIN - SET SHADER
    GLuint shaderProgram = makeProgram("shaders/basic.vert", "shaders/basic.frag");
    if (!shaderProgram) {
        std::cerr << "No pude crear el programa\n";
        exit(1);
    }
    GLint locMVP = glGetUniformLocation(shaderProgram, "MVP");

    glm::mat4 Model      = glm::mat4(1.0f);


    glm::mat4 Projection = glm::perspective(
        glm::radians(45.0f),
        800.0f / 600.0f,
        0.1f, 100.0f
    );

    /////////////////////////////////////////////////////////////////////////////////// MAIN - SET CAMERA
    // Cámara
    Camera cam;
    cam.updateVectors();
    gCam = &cam;

    // Desactivar cursor y recibir movimiento del mouse
    glfwSetInputMode(window.win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window.win, mouse_callback);

    /////////////////////////////////////////////////////////////////////////////////// WHILE
    while(!window.shouldClose()){

        glfwPollEvents();

        if (glfwGetKey(window.win, GLFW_KEY_Q) == GLFW_PRESS) {
            window.close();
            break;
        }

        glClearColor(0.039f, 0.015f, 0.1019f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        /////////////////////////////////////////////////////////////////////////////////// WHILE - camera WASD
        static float lastFrame = 0.0f;
        float currentFrame = glfwGetTime();
        float dt = currentFrame - lastFrame;
        lastFrame = currentFrame;

        float v = cam.speed * dt;

        if (glfwGetKey(window.win, GLFW_KEY_W) == GLFW_PRESS)
            cam.pos += cam.front * v;
        if (glfwGetKey(window.win, GLFW_KEY_S) == GLFW_PRESS)
            cam.pos -= cam.front * v;
        if (glfwGetKey(window.win, GLFW_KEY_A) == GLFW_PRESS)
            cam.pos -= cam.rightv * v;
        if (glfwGetKey(window.win, GLFW_KEY_D) == GLFW_PRESS)
            cam.pos += cam.rightv * v;

        if (glfwGetKey(window.win, GLFW_KEY_SPACE) == GLFW_PRESS)
            cam.pos.y += v;
        if (glfwGetKey(window.win, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            cam.pos.y -= v;


        
        /////////////////////////////////////////////////////////////////////////////////// WHILE - Rota el cubo
        float time = glfwGetTime();
        Model = glm::rotate(glm::mat4(1.0f), time, glm::vec3(0,1,0));
        glm::mat4 View = cam.getView();
        
        glm::mat4 MVP = Projection * View * Model;


        glUseProgram(shaderProgram);
        glUniformMatrix4fv(locMVP, 1, GL_FALSE, &MVP[0][0]);

        vao.bind();                   // activás tu geometry state (VBO + EBO + layout)
        glDrawElements(
            GL_TRIANGLES,            // tipo de primitivas
            indices.size(),          // cuántos índices
            GL_UNSIGNED_INT,         // tipo de los índices
            0                        // offset (en EBO)
        );
        vao.unbind();

        glfwSwapBuffers(window.win);

    }
    /////////////////////////////////////////////////////////////////////////////////// TERMINATE
    
    glDeleteProgram(shaderProgram);
    return 0;
}