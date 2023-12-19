#pragma once

#include <glad/glad.h>
#include <string>

class Shader {
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void use() const;
    unsigned int GetShader();

private:
    unsigned int shaderProgram;

    void checkCompileErrors(unsigned int shader, const std::string& type);
};