#include "Player.h"

Player::Player(sf::Vector2f position, sf::Color color)
    : mVelocity(0.f, 0.f), mIsJumping(false), mIsAttacking(false), mIsBlocking(false), mOnGround(true),
    mAlive(true), mHealth(3), mGravity(800.f), mJumpStrength(-400.f), mSpeed(200.f)
{
    // Player body
    mBody.setSize(sf::Vector2f(50, 100));  // Player size
    mBody.setPosition(position);           // Initial position
    mBody.setFillColor(color);             // Player color

    // Player's sword
    mSword.setSize(sf::Vector2f(40, 10));  // Sword size
    mSword.setFillColor(sf::Color::White); // Sword color
    mSword.setPosition(position.x + 50, position.y + 45);  // Sword starts by the player's side
}

void Player::handleInput(sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key jump, sf::Keyboard::Key attack, sf::Keyboard::Key block)
{
    mVelocity.x = 0.f;

    if (sf::Keyboard::isKeyPressed(left))
    {
        mVelocity.x = -mSpeed;  // Move left
        mSword.setPosition(mBody.getPosition().x - 40, mBody.getPosition().y + 45);  // Sword on the left
    }
    else if (sf::Keyboard::isKeyPressed(right))
    {
        mVelocity.x = mSpeed;   // Move right
        mSword.setPosition(mBody.getPosition().x + 50, mBody.getPosition().y + 45);  // Sword on the right
    }

    if (sf::Keyboard::isKeyPressed(jump) && mOnGround)
    {
        mIsJumping = true;
        mOnGround = false;
        mVelocity.y = mJumpStrength;  // Jump
    }

    if (sf::Keyboard::isKeyPressed(attack) && attackClock.getElapsedTime().asSeconds() > 0.5f)
    {
        mIsAttacking = true;
        mIsBlocking = false;
        attackClock.restart();
    }
    else
    {
        mIsAttacking = false;
    }

    if (sf::Keyboard::isKeyPressed(block))
    {
        mIsBlocking = true;
    }
    else
    {
        mIsBlocking = false;
    }
}

void Player::update(float deltaTime)
{
    if (!mOnGround)
    {
        mVelocity.y += mGravity * deltaTime;  // Apply gravity
    }

    // Move player
    mBody.move(mVelocity * deltaTime);
    mSword.move(mVelocity * deltaTime);

    // Ground collision detection
    if (mBody.getPosition().y + mBody.getSize().y >= 600)
    {
        mVelocity.y = 0;
        mIsJumping = false;
        mOnGround = true;
        mBody.setPosition(mBody.getPosition().x, 600 - mBody.getSize().y);
        mSword.setPosition(mBody.getPosition().x + (mVelocity.x > 0 ? 50 : -40), mBody.getPosition().y + 45); // Position the sword
    }
}

void Player::onCollide(const sf::FloatRect& platformBounds)
{
    // Ensure player lands on the platform correctly
    if (mVelocity.y > 0 && mBody.getGlobalBounds().intersects(platformBounds))
    {
        mVelocity.y = 0;
        mIsJumping = false;
        mOnGround = true;
        mBody.setPosition(mBody.getPosition().x, platformBounds.top - mBody.getSize().y);
        mSword.setPosition(mBody.getPosition().x + (mVelocity.x > 0 ? 50 : -40), mBody.getPosition().y + 45);
    }
}

void Player::takeDamage()
{
    mHealth--;
    if (mHealth <= 0)
    {
        mAlive = false;
    }
}

void Player::render(sf::RenderWindow& window)
{
    window.draw(mBody);
    window.draw(mSword);
}

sf::FloatRect Player::getBounds() const
{
    return mBody.getGlobalBounds();
}

bool Player::isAttacking() const
{
    return mIsAttacking;
}

bool Player::isBlocking() const
{
    return mIsBlocking;
}

bool Player::isAlive() const
{
    return mAlive;
}
