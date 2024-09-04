#include "Platform.h"

Platform::Platform(sf::Vector2f position, sf::Vector2f size)
{
    mBody.setSize(size);
    mBody.setPosition(position);
    mBody.setFillColor(sf::Color::Green);  // Platform color
}

void Platform::render(sf::RenderWindow& window) const
{
    window.draw(mBody);
}

sf::FloatRect Platform::getBounds() const
{
    return mBody.getGlobalBounds();
}
