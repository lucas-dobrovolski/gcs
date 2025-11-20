#pragma once
#include <vector>
#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ObjCtrl.h"
#include "../Object/Geometry.h"
#include "../Render/Shader.h"
#include "gsc.h"

namespace GSC {

class GPUCtrl {

    private:
        // guarda shaders como objetos
        std::vector<std::shared_ptr<Shader>> shaders;

    public:

        GPUCtrl();
        ~GPUCtrl();

        void setGladContext();

        std::shared_ptr<Shader> makeShader(const char* vs, const char* fs);
        std::shared_ptr<Mesh> uploadGeometry(const Geometry& geo);

        void render(const ObjCtrl& objCtrl, Shader& shader);
};

}
