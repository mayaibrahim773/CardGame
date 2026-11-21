#include "Room.hpp"

#include <stb_image.h>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

Room::Room()
{
    float vertices[] = {
        -0.5f, 0.0f, -0.5f, 0.0f, 0.0f,
        -0.5f, 0.0f,  0.5f, 0.0f, 1.0f,
         0.5f, 0.0f,  0.5f, 1.0f, 1.0f,
         0.5f, 0.0f, -0.5f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        5 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        5 * sizeof(float),
        (void*)(3 * sizeof(float))
    );

    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    float cubeVertices[] = {
        -0.5f,-0.5f, 0.5f,  0.5f,-0.5f, 0.5f,  0.5f, 0.5f, 0.5f,
        -0.5f,-0.5f, 0.5f,  0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f,

         0.5f,-0.5f,-0.5f, -0.5f,-0.5f,-0.5f, -0.5f, 0.5f,-0.5f,
         0.5f,-0.5f,-0.5f, -0.5f, 0.5f,-0.5f,  0.5f, 0.5f,-0.5f,

        -0.5f,-0.5f,-0.5f, -0.5f,-0.5f, 0.5f, -0.5f, 0.5f, 0.5f,
        -0.5f,-0.5f,-0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f,-0.5f,

         0.5f,-0.5f, 0.5f,  0.5f,-0.5f,-0.5f,  0.5f, 0.5f,-0.5f,
         0.5f,-0.5f, 0.5f,  0.5f, 0.5f,-0.5f,  0.5f, 0.5f, 0.5f,

        -0.5f, 0.5f, 0.5f,  0.5f, 0.5f, 0.5f,  0.5f, 0.5f,-0.5f,
        -0.5f, 0.5f, 0.5f,  0.5f, 0.5f,-0.5f, -0.5f, 0.5f,-0.5f,

        -0.5f,-0.5f,-0.5f,  0.5f,-0.5f,-0.5f,  0.5f,-0.5f, 0.5f,
        -0.5f,-0.5f,-0.5f,  0.5f,-0.5f, 0.5f, -0.5f,-0.5f, 0.5f
    };

    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);

    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(cubeVertices),
        cubeVertices,
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    float posterVertices[] = {
        -1.0f, -0.7f, 0.0f, 0.0f, 0.0f,
         1.0f, -0.7f, 0.0f, 1.0f, 0.0f,
         1.0f,  0.3f, 0.0f, 1.0f, 0.7f,
         0.6f,  0.7f, 0.0f, 0.8f, 1.0f,
        -1.0f,  0.7f, 0.0f, 0.0f, 1.0f
    };

    glGenVertexArrays(1, &posterVAO);
    glGenBuffers(1, &posterVBO);

    glBindVertexArray(posterVAO);
    glBindBuffer(GL_ARRAY_BUFFER, posterVBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(posterVertices),
        posterVertices,
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        5 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        5 * sizeof(float),
        (void*)(3 * sizeof(float))
    );

    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    woodTexture = loadTexture(
        "./textures/room/wood.png"
    );

    wallpaperTexture = loadTexture(
        "./textures/room/wallpaper.jpg"
    );

    artworkTexture = loadTexture(
        "./textures/poster/artwork.jpg"
    );
}

GLuint Room::loadTexture(const std::string& path)
{
    int width = 0;
    int height = 0;
    int channels = 0;

    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load(
        path.c_str(),
        &width,
        &height,
        &channels,
        0
    );

    if (!data)
    {
        std::cout
            << "Failed to load texture: "
            << path
            << std::endl;

        return 0;
    }

    GLenum format = GL_RGB;

    if (channels == 1)
    {
        format = GL_RED;
    }
    else if (channels == 4)
    {
        format = GL_RGBA;
    }

    GLuint texture = 0;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_S,
        GL_REPEAT
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_T,
        GL_REPEAT
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,
        GL_LINEAR_MIPMAP_LINEAR
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER,
        GL_LINEAR
    );

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        format,
        width,
        height,
        0,
        format,
        GL_UNSIGNED_BYTE,
        data
    );

    glGenerateMipmap(GL_TEXTURE_2D);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

void Room::drawSurface(
    Shader& shader,
    const glm::mat4& model,
    GLuint texture,
    const glm::vec3& tint
)
{
    shader.use();

    shader.setBool("useTexture", true);
    shader.setVec3("objectColor", tint);
    shader.setMat4("model", model);
    shader.setInt("texture_diffuse1", 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBindVertexArray(VAO);

    glDrawArrays(
        GL_TRIANGLE_FAN,
        0,
        4
    );

    glBindVertexArray(0);
}

void Room::drawBox(
    Shader& shader,
    const glm::vec3& position,
    const glm::vec3& size,
    const glm::vec3& color
)
{
    glm::mat4 model(1.0f);

    model = glm::translate(
        model,
        position
    );

    model = glm::scale(
        model,
        size
    );

    shader.use();

    shader.setBool("useTexture", false);
    shader.setVec3("objectColor", color);
    shader.setMat4("model", model);

    glBindVertexArray(cubeVAO);

    glDrawArrays(
        GL_TRIANGLES,
        0,
        36
    );

    glBindVertexArray(0);
}

void Room::drawBookshelf(Shader& shader)
{
    glm::vec3 darkWood(
        0.30f,
        0.15f,
        0.07f
    );

    glm::vec3 lightWood(
        0.48f,
        0.27f,
        0.12f
    );

    drawBox(
        shader,
        {-6.8f, 1.4f, -6.7f},
        {0.18f, 2.8f, 0.8f},
        darkWood
    );

    drawBox(
        shader,
        {-4.6f, 1.4f, -6.7f},
        {0.18f, 2.8f, 0.8f},
        darkWood
    );

    for (int i = 0; i < 4; i++)
    {
        drawBox(
            shader,
            {-5.7f, 0.1f + i * 0.85f, -6.7f},
            {2.4f, 0.12f, 0.8f},
            lightWood
        );
    }

    for (int row = 0; row < 3; row++)
    {
        for (int i = 0; i < 7; i++)
        {
            glm::vec3 color(
                0.20f + 0.08f * (i % 3),
                0.12f + 0.06f * (row % 2),
                0.25f + 0.07f * (i % 2)
            );

            drawBox(
                shader,
                {
                    -6.55f + i * 0.28f,
                    0.55f + row * 0.85f,
                    -6.55f
                },
                {0.20f, 0.65f, 0.4f},
                color
            );
        }
    }
}

void Room::drawLamp(Shader& shader)
{
    glm::vec3 gold(
        0.58f,
        0.39f,
        0.16f
    );

    drawBox(
        shader,
        {5.5f, 0.0f, -5.5f},
        {0.9f, 0.2f, 0.9f},
        gold
    );

    drawBox(
        shader,
        {5.5f, 1.2f, -5.5f},
        {0.12f, 2.4f, 0.12f},
        gold
    );

    drawBox(
        shader,
        {5.5f, 2.55f, -5.5f},
        {1.3f, 0.75f, 1.3f},
        {0.82f, 0.68f, 0.42f}
    );

    drawBox(
        shader,
        {5.5f, 2.95f, -5.5f},
        {0.75f, 0.1f, 0.75f},
        gold
    );
}

void Room::drawChest(Shader& shader)
{
    glm::vec3 wood(
        0.38f,
        0.19f,
        0.08f
    );

    glm::vec3 gold(
        0.58f,
        0.40f,
        0.18f
    );

    drawBox(
        shader,
        {4.5f, 0.25f, 1.5f},
        {1.8f, 0.8f, 1.1f},
        wood
    );

    drawBox(
        shader,
        {4.5f, 0.7f, 1.5f},
        {1.9f, 0.15f, 1.2f},
        gold
    );

    drawBox(
        shader,
        {3.9f, 0.3f, 2.06f},
        {0.12f, 0.65f, 0.06f},
        gold
    );

    drawBox(
        shader,
        {5.1f, 0.3f, 2.06f},
        {0.12f, 0.65f, 0.06f},
        gold
    );

    drawBox(
        shader,
        {4.5f, 0.35f, 2.1f},
        {0.28f, 0.25f, 0.08f},
        gold
    );
}

void Room::drawPoster(Shader& shader)
{
    glm::mat4 model(1.0f);

    model = glm::translate(
        model,
        glm::vec3(0.0f, 4.0f, -7.94f)
    );

    model = glm::scale(
        model,
        glm::vec3(2.2f, 2.2f, 1.0f)
    );

    shader.use();

    shader.setBool("useTexture", true);

    shader.setVec3(
        "objectColor",
        glm::vec3(1.0f)
    );

    shader.setMat4("model", model);
    shader.setInt("texture_diffuse1", 0);

    glActiveTexture(GL_TEXTURE0);

    glBindTexture(
        GL_TEXTURE_2D,
        artworkTexture
    );

    glBindVertexArray(posterVAO);

    glDrawArrays(
        GL_TRIANGLE_FAN,
        0,
        5
    );

    glBindVertexArray(0);
}

void Room::draw(Shader& shader, bool showCeiling)
{
    // Floor
    glm::mat4 floorModel(1.0f);

    floorModel = glm::translate(
        floorModel,
        glm::vec3(0.0f, -0.15f, 0.0f)
    );

    floorModel = glm::scale(
        floorModel,
        glm::vec3(16.0f, 1.0f, 16.0f)
    );

    drawSurface(
        shader,
        floorModel,
        woodTexture
    );

    // Back wall
    glm::mat4 backWall(1.0f);

    backWall = glm::translate(
        backWall,
        glm::vec3(0.0f, 3.85f, -8.0f)
    );

    backWall = glm::rotate(
        backWall,
        glm::radians(90.0f),
        glm::vec3(1.0f, 0.0f, 0.0f)
    );

    backWall = glm::scale(
        backWall,
        glm::vec3(16.0f, 1.0f, 8.0f)
    );

    drawSurface(
        shader,
        backWall,
        wallpaperTexture
    );

    // Left wall
    glm::mat4 leftWall(1.0f);

    leftWall = glm::translate(
        leftWall,
        glm::vec3(-8.0f, 3.85f, 0.0f)
    );

    leftWall = glm::rotate(
        leftWall,
        glm::radians(90.0f),
        glm::vec3(0.0f, 0.0f, 1.0f)
    );

    leftWall = glm::scale(
        leftWall,
        glm::vec3(8.0f, 1.0f, 16.0f)
    );

    drawSurface(
        shader,
        leftWall,
        wallpaperTexture
    );

    // Right wall
    glm::mat4 rightWall(1.0f);

    rightWall = glm::translate(
        rightWall,
        glm::vec3(8.0f, 3.85f, 0.0f)
    );

    rightWall = glm::rotate(
        rightWall,
        glm::radians(90.0f),
        glm::vec3(0.0f, 0.0f, 1.0f)
    );

    rightWall = glm::scale(
        rightWall,
        glm::vec3(8.0f, 1.0f, 16.0f)
    );

    drawSurface(
        shader,
        rightWall,
        wallpaperTexture
    );

    // Partial dark ceiling
if (showCeiling)
{
    glm::mat4 ceilingModel(1.0f);

    ceilingModel = glm::translate(
        ceilingModel,
        glm::vec3(0.0f, 7.65f, -5.6f)
    );

    ceilingModel = glm::scale(
        ceilingModel,
        glm::vec3(16.0f, 1.0f, 3.5f)
    );

    drawSurface(
        shader,
        ceilingModel,
        wallpaperTexture,
        glm::vec3(0.85f, 0.65f, 0.68f)
    );
}

    // Furniture and decorations
    drawBookshelf(shader);

    drawLamp(shader);

    drawChest(shader);

    drawPoster(shader);
}