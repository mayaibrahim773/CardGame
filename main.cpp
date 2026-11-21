#include "Game.hpp"
#include "Table.hpp"
#include "Room.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <learnopengl/shader_m.h>

#include <algorithm>
#include <iostream>

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

// Camera animation
float cameraBlend = 1.0f;
float targetCameraBlend = 1.0f;
float cameraStartBlend = 0.0f;
float cameraTransitionTime = 1.0f;

const float CAMERA_DURATION = 1.0f;

// Keyboard
bool gWasPressed = false;
bool playRequested = false;

void framebuffer_size_callback(
    GLFWwindow* window,
    int width,
    int height
)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    // Top camera
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS &&
        targetCameraBlend != 0.0f)
    {
        cameraStartBlend = cameraBlend;
        targetCameraBlend = 0.0f;
        cameraTransitionTime = 0.0f;
    }

    // Player camera
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS &&
        targetCameraBlend != 1.0f)
    {
        cameraStartBlend = cameraBlend;
        targetCameraBlend = 1.0f;
        cameraTransitionTime = 0.0f;
    }

    // Play one card per key press
    bool gPressed =
        glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS;

    if (gPressed && !gWasPressed)
    {
        playRequested = true;
    }

    gWasPressed = gPressed;
}

int main()
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    glfwWindowHint(
        GLFW_OPENGL_PROFILE,
        GLFW_OPENGL_CORE_PROFILE
    );

    GLFWwindow* window = glfwCreateWindow(
        SCR_WIDTH,
        SCR_HEIGHT,
        "Card Game",
        nullptr,
        nullptr
    );

    if (!window)
    {
        std::cout << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(
        window,
        framebuffer_size_callback
    );

    if (!gladLoadGLLoader(
        (GLADloadproc)glfwGetProcAddress
    ))
    {
        std::cout << "Failed to initialize GLAD\n";
        glfwTerminate();
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    Shader shader(
        "./shaders/CardGame.vs",
        "./shaders/CardGame.fs"
    );

    Table table;
    Game game;
    Room room;

    float lastFrame =
        static_cast<float>(glfwGetTime());

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame =
            static_cast<float>(glfwGetTime());

        float deltaTime =
            currentFrame - lastFrame;

        lastFrame = currentFrame;

        deltaTime = std::min(deltaTime, 0.05f);

        processInput(window);

        // Play a random card
        if (playRequested)
        {
            game.playRandomCard();
            playRequested = false;
        }

        // Smooth camera transition
        if (cameraTransitionTime < CAMERA_DURATION)
        {
            cameraTransitionTime = std::min(
                cameraTransitionTime + deltaTime,
                CAMERA_DURATION
            );

            float t =
                cameraTransitionTime / CAMERA_DURATION;

            t = t * t * (3.0f - 2.0f * t);

            cameraBlend = glm::mix(
                cameraStartBlend,
                targetCameraBlend,
                t
            );
        }
        else
        {
            cameraBlend = targetCameraBlend;
        }

        game.update(cameraBlend, deltaTime);

        glClearColor(
            0.12f,
            0.12f,
            0.16f,
            1.0f
        );

        glClear(
            GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT
        );

        shader.use();

        int width = 0;
        int height = 0;

        glfwGetFramebufferSize(
            window,
            &width,
            &height
        );

        float aspect =
            static_cast<float>(width) /
            static_cast<float>(std::max(height, 1));

        glm::mat4 projection = glm::perspective(
            glm::radians(50.0f),
            aspect,
            0.1f,
            100.0f
        );

      // Camera 1: top view
glm::vec3 topCamera(
    0.0f,
    6.5f,
    0.01f
);

// Camera 2: player view
glm::vec3 playerCamera(
    0.0f,
    4.8f,
    9.0f
);

glm::vec3 topTarget(
    0.0f,
    0.85f,
    0.0f
);

glm::vec3 playerTarget(
    0.0f,
    2.5f,
    -1.0f
);

glm::vec3 cameraPosition = glm::mix(
    topCamera,
    playerCamera,
    cameraBlend
);

glm::vec3 cameraTarget = glm::mix(
    topTarget,
    playerTarget,
    cameraBlend
);

glm::vec3 topUp(
    0.0f,
    0.0f,
    -1.0f
);

glm::vec3 playerUp(
    0.0f,
    1.0f,
    0.0f
);

glm::vec3 cameraUp = glm::normalize(
    glm::mix(topUp, playerUp, cameraBlend)
);

glm::mat4 view = glm::lookAt(
    cameraPosition,
    cameraTarget,
    cameraUp
);
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        room.draw(shader, cameraBlend>0.85f);
        table.draw(shader);
        game.draw(shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}