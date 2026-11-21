#include "Game.hpp"

#include <glm/common.hpp>

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <string>
#include <vector>

Game::Game()
{
    std::srand(
        static_cast<unsigned int>(std::time(nullptr))
    );

    for (int i = 0; i < 5; i++)
    {
        glm::vec3 position(
            -2.0f + static_cast<float>(i),
            0.92f,
            1.3f
        );

        std::string imagePath =
            "./textures/cards/card" +
            std::to_string(i + 1) +
            ".jpg";

        cards.push_back(
            std::make_unique<Card>(
                imagePath,
                position
            )
        );

        CardState state;

        state.startPosition = position;
        state.targetPosition = position;

        states.push_back(state);
    }
}

void Game::playRandomCard()
{
    if (playedCount >= 5)
    {
        return;
    }

    std::vector<int> available;

    for (int i = 0; i < static_cast<int>(states.size()); i++)
    {
        if (!states[i].played)
        {
            available.push_back(i);
        }
    }

    if (available.empty())
    {
        return;
    }

    int randomIndex =
        std::rand() % static_cast<int>(available.size());

    int selected = available[randomIndex];

    states[selected].played = true;
    states[selected].moving = true;
    states[selected].progress = 0.0f;

    states[selected].targetPosition = glm::vec3(
    -2.0f + static_cast<float>(playedCount),
    0.92f,
    0.0f
);

    playedCount++;
}

void Game::update(
    float cameraBlend,
    float deltaTime
)
{
    float angle = 90.0f * cameraBlend;

    const float CARD_MOVE_DURATION = 0.9f;
    const float CARD_LIFT_HEIGHT = 0.45f;

    const float PI = 3.14159265f;

    for (int i = 0; i < static_cast<int>(cards.size()); i++)
    {
        cards[i]->setRotation(angle);

        CardState& state = states[i];

        if (state.moving)
        {
            state.progress = glm::clamp(
                state.progress +
                deltaTime / CARD_MOVE_DURATION,
                0.0f,
                1.0f
            );

            float t = state.progress;

            t = t * t * (3.0f - 2.0f * t);

            glm::vec3 newPosition = glm::mix(
                state.startPosition,
                state.targetPosition,
                t
            );

            float lift =
                CARD_LIFT_HEIGHT * std::sin(t * PI);

            newPosition.y += lift;

            cards[i]->setPosition(newPosition);

            if (state.progress >= 1.0f)
            {
                state.moving = false;

                cards[i]->setPosition(
                    state.targetPosition
                );
            }
        }
    }
}

void Game::draw(Shader& shader)
{
    for (auto& card : cards)
    {
        card->draw(shader);
    }
}