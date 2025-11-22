#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>

namespace GSC {

class Shader {
public:
    // Crea y linkea un shader desde código fuente en memoria
    Shader(const char* vertexSrc, const char* fragmentSrc);

    // Carga desde archivos (opcional, útil más adelante)
    Shader(const std::string& vertexPath, const std::string& fragmentPath);

    ~Shader();

    // Activar el programa
    void use() const;

    // Uniform setters
    void setMat4(const char* name, const glm::mat4& value) const;
    void setVec3(const char* name, const glm::vec3& value) const;
    void setFloat(const char* name, float value) const;
    void setInt(const char* name, int value) const;

    GLuint getProgram() const { return program; }

private:
    GLuint program = 0;

    GLuint compile(GLenum type, const char* src);
    GLint uniformLoc(const char* name) const;

    // Ayuda para cargar desde archivo
    static std::string loadFile(const std::string& path);
};

} // namespace GSC
