#include "Game.h"

Game::Game()
    : mWindow(sf::VideoMode(800, 600), "Nidhogg-like Game"),
    player1(sf::Vector2f(100, 500), sf::Color::Blue),
    player2(sf::Vector2f(700, 500), sf::Color::Red),
    gameOver(false)
{
    // Load font for victory text
    font.loadFromFile("arial.ttf");
    victoryText.setFont(font);
    victoryText.setCharacterSize(50);
    victoryText.setFillColor(sf::Color::White);
    victoryText.setPosition(200, 250);

    // Create platforms
    platforms.push_back(Platform(sf::Vector2f(0, 550), sf::Vector2f(800, 50)));   // Ground platform
    platforms.push_back(Platform(sf::Vector2f(300, 400), sf::Vector2f(200, 20))); // Middle platform
}

void Game::run()
{
    sf::Clock clock;

    while (mWindow.isOpen())
    {
        processEvents();

        float deltaTime = clock.restart().asSeconds();
        if (!gameOver)
        {
            update(deltaTime);
        }
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            mWindow.close();
        }
    }

    // Player input
    player1.handleInput(sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::Space, sf::Keyboard::LShift);
    player2.handleInput(sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Enter, sf::Keyboard::RShift);
}

void Game::update(float deltaTime)
{
    player1.update(deltaTime);
    player2.update(deltaTime);

    // Platform collision detection
    for (const auto& platform : platforms)
    {
        player1.onCollide(platform.getBounds());
        player2.onCollide(platform.getBounds());
    }

    // Combat logic: If players collide and attack
    if (player1.getBounds().intersects(player2.getBounds()))
    {
        if (player1.isAttacking() && !player2.isBlocking())
        {
            player2.takeDamage();
        }
        else if (player2.isAttacking() && !player1.isBlocking())
        {
            player1.takeDamage();
        }

        if (!player1.isAlive())
        {
            gameOver = true;
            victoryText.setString("Player 2 Wins!");
        }
        else if (!player2.isAlive())
        {
            gameOver = true;
            victoryText.setString("Player 1 Wins!");
        }
    }
}

void Game::render()
{
    mWindow.clear();

    if (!gameOver)
    {
        // Render platforms
        for (const auto& platform : platforms)
        {
            platform.render(mWindow);
        }

        // Render players
        player1.render(mWindow);
        player2.render(mWindow);
    }
    else
    {
        mWindow.draw(victoryText);  // Display victory message
    }

    mWindow.display();
}
