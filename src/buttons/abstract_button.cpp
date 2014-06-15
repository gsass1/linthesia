#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "abstract_button.h"


namespace linthesia {

/**
 *
 */
AbstractButton::AbstractButton(
    const std::string &_text
) {
    currentState = ButtonStates::NORMAL;

    //TODO: replace hardcoded strings by something better
    if (!texture.loadFromFile("../graphics/button.png")) {
        std::cerr << "Can't load button.png" << std::endl;
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);

    if (!font.loadFromFile("../fonts/FaunaOne-Regular.ttf")) {
        std::cerr << "Can't load font FaunaOne-Regular" << std::endl;
    }
    label.setFont(font);
    label.setString(_text);

    //We center the text inside the button
    label.setPosition(
        (sprite.getLocalBounds().width - label.getLocalBounds().width) / 2.0f,
        // TODO: logically it should be  / 2.0 but then it's not centered etc..
        // need to figure out why
        (sprite.getLocalBounds().height - label.getLocalBounds().height) / 4.0f
    );

}

/**
 *
 */
bool AbstractButton::actionTriggered(const sf::Window &app) {
    if (containsPoint(sf::Mouse::getPosition(app))) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            // only if we left click inside the button
            // we will consider the action of this button
            // triggered
            return true;
        }
        setHovered();
    } else {
        setUnhovered();
    }
    return false;
}

/**
 *
 */
bool AbstractButton::containsPoint(sf::Vector2i point) const {
    // we subtract the x,y position of the button itself
    // as the point given in parameter has its coordinate relative to
    // the window
    return getGlobalBounds().contains(
        point.x - getPosition().x,
        point.y - getPosition().y
    );
}

/**
 *
 */
sf::FloatRect AbstractButton::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

/**
 *
 */
void AbstractButton::setHovered() {
    if (currentState == ButtonStates::HOVERED) {
        return;
    }
    currentState = ButtonStates::HOVERED;
    sprite.setColor(sf::Color(200,200,200));
    label.setColor(sf::Color(200,200,200));
}

/**
 *
 */
void AbstractButton::setUnhovered() {
    if (currentState != ButtonStates::HOVERED) {
        return;
    }
    currentState = ButtonStates::NORMAL;
    sprite.setColor(sf::Color::White);
    label.setColor(sf::Color::White);
}

/**
 *
 */
void AbstractButton::draw(
    sf::RenderTarget& target,
    sf::RenderStates states
) const {
    states.transform *= getTransform();
    target.draw(sprite, states);
    target.draw(label, states);
}

}