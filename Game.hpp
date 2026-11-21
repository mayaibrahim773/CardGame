#pragma once

#include "Card.hpp"

#include <glm/glm.hpp>

#include <memory>
#include <vector>

class Game
{
public:
    Game();

    void draw(Shader& shader);
    void update(float cameraBlend, float deltaTime);
    void playRandomCard();

private:
    struct CardState
    {
        glm::vec3 startPosition;
        glm::vec3 targetPosition;

        float progress = 0.0f;
        bool played = false;
        bool moving = false;
    };

    std::vector<std::unique_ptr<Card>> cards;
    std::vector<CardState> states;

    int playedCount = 0;
};