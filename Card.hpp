#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <learnopengl/shader_m.h>

#include <string>

class Card
{
public:
    Card(const std::string& imagePath, glm::vec3 startPosition);

    void draw(Shader& shader);

    void setPosition(glm::vec3 newPosition);
    void setRotation(float newRotation);

private:
    GLuint VAO = 0;
    GLuint VBO = 0;

    GLuint borderVAO = 0;
    GLuint borderVBO = 0;

    GLuint textureID = 0;

    glm::vec3 position;
    float rotation = 0.0f;
};