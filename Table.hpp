#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <learnopengl/shader_m.h>

class Table
{
public:
    Table();

    void draw(Shader& shader);

private:
    GLuint VAO = 0;
    GLuint VBO = 0;

    void drawBox(
        Shader& shader,
        const glm::vec3& position,
        const glm::vec3& size,
        const glm::vec3& color
    );
};