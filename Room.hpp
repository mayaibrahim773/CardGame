#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <learnopengl/shader_m.h>

#include <string>

class Room
{
public:
    Room();

    void draw(Shader& shader, bool showCeiling);

private:
    GLuint VAO = 0;
    GLuint VBO = 0;

    GLuint floorVAO = 0;
    GLuint floorVBO = 0;

    GLuint cubeVAO = 0;
    GLuint cubeVBO = 0;

    GLuint posterVAO = 0;
    GLuint posterVBO = 0;

    GLuint woodTexture = 0;
    GLuint wallpaperTexture = 0;
    GLuint artworkTexture = 0;

    GLuint loadTexture(const std::string& path);

   void drawSurface(
    Shader& shader,
    const glm::mat4& model,
    GLuint texture,
    const glm::vec3& tint = glm::vec3(1.0f)
);

    void drawBox(
        Shader& shader,
        const glm::vec3& position,
        const glm::vec3& size,
        const glm::vec3& color
    );

    void drawPoster(Shader& shader);
    void drawBookshelf(Shader& shader);
    void drawLamp(Shader& shader);
    void drawChest(Shader& shader);
};