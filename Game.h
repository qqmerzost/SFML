#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Platform.h"
#include <vector>

class Game
{
public:
    Game();
    void run();

private:
    void processEvents();
    void update(float deltaTime);
    void render();

    sf::RenderWindow mWindow;
    Player player1;
    Player player2;
    std::vector<Platform> platforms;
    sf::Font font;
    sf::Text victoryText;
    bool gameOver;
};
