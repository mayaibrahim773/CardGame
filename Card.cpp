#include "Card.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>

#include <vector>
#include <iostream>
#include <cmath>

Card::Card(
    const std::string& imagePath,
    glm::vec3 startPosition
)
{
    position = startPosition;

    // ==========================================
    // 1. Create the card image
    // ==========================================

    // The image is slightly smaller than the border.
    // This makes the golden frame visible.

    std::vector<glm::vec3> vertices = {
        {-0.345f, 0.002f, -0.470f},
        {-0.345f, 0.002f,  0.470f},
        { 0.345f, 0.002f,  0.470f},
        { 0.345f, 0.002f, -0.470f}
    };

    std::vector<glm::vec2> texcoords = {
        {1.0f, 1.0f},
        {1.0f, 0.0f},
        {0.0f, 0.0f},
        {0.0f, 1.0f}
    };

    std::vector<float> data;

    for (int i = 0; i < 4; i++)
    {
        data.push_back(vertices[i].x);
        data.push_back(vertices[i].y);
        data.push_back(vertices[i].z);

        data.push_back(texcoords[i].x);
        data.push_back(texcoords[i].y);
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        data.size() * sizeof(float),
        data.data(),
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

    // ==========================================
    // 2. Create the golden border
    // ==========================================

    // The border is slightly larger than the image.

    float borderVertices[] = {

        -0.375f, 0.0f, -0.5f,
        -0.375f, 0.0f,  0.5f,
         0.375f, 0.0f,  0.5f,
         0.375f, 0.0f, -0.5f
    };

    glGenVertexArrays(1, &borderVAO);
    glGenBuffers(1, &borderVBO);

    glBindVertexArray(borderVAO);
    glBindBuffer(GL_ARRAY_BUFFER, borderVBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(borderVertices),
        borderVertices,
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

    // ==========================================
    // 3. Load the card texture
    // ==========================================

    int width = 0;
    int height = 0;
    int channels = 0;

    stbi_set_flip_vertically_on_load(true);

    unsigned char* image = stbi_load(
        imagePath.c_str(),
        &width,
        &height,
        &channels,
        0
    );

    if (!image)
    {
        std::cout
            << "Failed to load card texture: "
            << imagePath
            << std::endl;

        return;
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

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_S,
        GL_CLAMP_TO_EDGE
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_T,
        GL_CLAMP_TO_EDGE
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
        image
    );

    glGenerateMipmap(GL_TEXTURE_2D);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    stbi_image_free(image);

    glBindTexture(GL_TEXTURE_2D, 0);
}

// ==========================================
// 4. Update card position
// ==========================================

void Card::setPosition(glm::vec3 newPosition)
{
    position = newPosition;
}

// ==========================================
// 5. Update card rotation
// ==========================================

void Card::setRotation(float newRotation)
{
    rotation = newRotation;
}

// ==========================================
// 6. Draw the card with its golden border
// ==========================================

void Card::draw(Shader& shader)
{
    float heightOffset =
        0.5f * std::sin(glm::radians(rotation));

    glm::mat4 model(1.0f);

    model = glm::translate(
        model,
        position + glm::vec3(
            0.0f,
            heightOffset,
            0.0f
        )
    );

    model = glm::rotate(
        model,
        glm::radians(rotation),
        glm::vec3(1.0f, 0.0f, 0.0f)
    );

    shader.use();

    shader.setMat4("model", model);

    // ======================================
    // Draw the golden border first
    // ======================================

    shader.setBool("useTexture", false);

    shader.setVec3(
        "objectColor",
        glm::vec3(
            0.85f,
            0.65f,
            0.20f
        )
    );

    glBindVertexArray(borderVAO);

    glDrawArrays(
        GL_TRIANGLE_FAN,
        0,
        4
    );

    glBindVertexArray(0);

    // ======================================
    // Draw the character image
    // ======================================

    shader.setBool("useTexture", true);

    shader.setVec3(
        "objectColor",
        glm::vec3(1.0f)
    );

    shader.setInt("texture_diffuse1", 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBindVertexArray(VAO);

    glDrawArrays(
        GL_TRIANGLE_FAN,
        0,
        4
    );

    glBindVertexArray(0);
}