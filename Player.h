#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
    Player(sf::Vector2f position, sf::Color color);

    void handleInput(sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key jump, sf::Keyboard::Key attack, sf::Keyboard::Key block);
    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    void onCollide(const sf::FloatRect& platformBounds);
    void takeDamage();

    sf::FloatRect getBounds() const;
    bool isAttacking() const;
    bool isBlocking() const;
    bool isAlive() const;

private:
    sf::RectangleShape mBody;
    sf::RectangleShape mSword;
    sf::Vector2f mVelocity;
    bool mIsJumping;
    bool mIsAttacking;
    bool mIsBlocking;
    bool mOnGround;
    bool mAlive;
    int mHealth;  // Health for the player
    float mGravity;
    float mJumpStrength;
    float mSpeed;
    sf::Clock attackClock;
};
