#pragma once

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

#include "window.hpp"
#include "common.hpp"
#include "shader_utils.hpp"
#include "VAO.hpp"

/////////////////////////////////////////////////////////////////////////////////// DEF framebuffer_size_callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // OpenGL actualiza su viewport al nuevo tamaño
    glViewport(0, 0, width, height);
}
/////////////////////////////////////////////////////////////////////////////////// DEF readFile

/////////////////////////////////////////////////////////////////////////////////// DEF CLASS VAO

/////////////////////////////////////////////////////////////////////////////////// def CAMERA
struct Camera {
    glm::vec3 pos    = glm::vec3(10.0f, 10.0f, 10.0f);
    float phi        = -135.0f;   // apunta al origen desde la diagonal
    float theta      = -30.0f;

    float speed      = 3.0f;
    float sens       = 0.1f;

    glm::vec3 front  = glm::vec3(0,0,-1);
    glm::vec3 up     = glm::vec3(0,1,0);
    glm::vec3 rightv = glm::vec3(1,0,0);

    void updateVectors() {
        float cy = glm::radians(phi);
        float cp = glm::radians(theta);

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

    gCam->phi   += dx * gCam->sens;
    gCam->theta += dy * gCam->sens;

    if (gCam->theta > 89.0f) gCam->theta = 89.0f;
    if (gCam->theta < -89.0f) gCam->theta = -89.0f;

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