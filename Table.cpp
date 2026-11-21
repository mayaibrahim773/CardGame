#include "Table.hpp"

#include <glm/gtc/matrix_transform.hpp>

Table::Table()
{
    float vertices[] = {
        -0.5f,-0.5f, 0.5f,
         0.5f,-0.5f, 0.5f,
         0.5f, 0.5f, 0.5f,

        -0.5f,-0.5f, 0.5f,
         0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,

         0.5f,-0.5f,-0.5f,
        -0.5f,-0.5f,-0.5f,
        -0.5f, 0.5f,-0.5f,

         0.5f,-0.5f,-0.5f,
        -0.5f, 0.5f,-0.5f,
         0.5f, 0.5f,-0.5f,

        -0.5f,-0.5f,-0.5f,
        -0.5f,-0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,

        -0.5f,-0.5f,-0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f,-0.5f,

         0.5f,-0.5f, 0.5f,
         0.5f,-0.5f,-0.5f,
         0.5f, 0.5f,-0.5f,

         0.5f,-0.5f, 0.5f,
         0.5f, 0.5f,-0.5f,
         0.5f, 0.5f, 0.5f,

        -0.5f, 0.5f, 0.5f,
         0.5f, 0.5f, 0.5f,
         0.5f, 0.5f,-0.5f,

        -0.5f, 0.5f, 0.5f,
         0.5f, 0.5f,-0.5f,
        -0.5f, 0.5f,-0.5f,

        -0.5f,-0.5f,-0.5f,
         0.5f,-0.5f,-0.5f,
         0.5f,-0.5f, 0.5f,

        -0.5f,-0.5f,-0.5f,
         0.5f,-0.5f, 0.5f,
        -0.5f,-0.5f, 0.5f
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
        0, 3, GL_FLOAT, GL_FALSE,
        3 * sizeof(float), (void*)0
    );

    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Table::drawBox(
    Shader& shader,
    const glm::vec3& position,
    const glm::vec3& size,
    const glm::vec3& color
)
{
    glm::mat4 model(1.0f);

    model = glm::translate(model, position);
    model = glm::scale(model, size);

    shader.use();

    shader.setBool("useTexture", false);
    shader.setVec3("objectColor", color);
    shader.setMat4("model", model);

    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);
}

void Table::draw(Shader& shader)
{
    glm::vec3 darkWood(
        0.22f, 0.105f, 0.045f
    );

    glm::vec3 warmWood(
        0.38f, 0.19f, 0.085f
    );

    glm::vec3 forestGreen(
        0.12f, 0.29f, 0.20f
    );

    glm::vec3 slateBlue(
        0.19f, 0.24f, 0.36f
    );

    glm::vec3 burgundy(
        0.34f, 0.13f, 0.15f
    );

    drawBox(
        shader,
        {0.0f, 0.73f, 0.0f},
        {6.0f, 0.24f, 4.0f},
        darkWood
    );

    drawBox(
        shader,
        {0.0f, 0.86f, 0.0f},
        {5.85f, 0.02f, 3.85f},
        warmWood
    );

    drawBox(
        shader,
        {-2.65f, 0.30f, -1.65f},
        {0.35f, 0.85f, 0.35f},
        darkWood
    );

    drawBox(
        shader,
        {2.65f, 0.30f, -1.65f},
        {0.35f, 0.85f, 0.35f},
        darkWood
    );

    drawBox(
        shader,
        {-2.65f, 0.30f, 1.65f},
        {0.35f, 0.85f, 0.35f},
        darkWood
    );

    drawBox(
        shader,
        {2.65f, 0.30f, 1.65f},
        {0.35f, 0.85f, 0.35f},
        darkWood
    );

    drawBox(
        shader,
        {0.0f, 0.885f, 1.3f},
        {5.5f, 0.015f, 0.9f},
        forestGreen
    );

    drawBox(
        shader,
        {0.0f, 0.885f, 0.0f},
        {5.5f, 0.015f, 1.1f},
        slateBlue
    );

    drawBox(
        shader,
        {0.0f, 0.885f, -1.3f},
        {5.5f, 0.015f, 0.9f},
        burgundy
    );
}