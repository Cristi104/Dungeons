#include "../include/Button.h"
#include <SFML/Window/Mouse.hpp>

Button::Button() {
    this->setPriority(4);
    this->boundingBox = sf::IntRect(0,0,50,50);
    this->wasPressed = false;
}

///Returns true for the first frame in witch the button is
///pressed resetting when the user no longer holds down M1
bool Button::isPressed() {
    bool Pressed;
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        int x = sf::Mouse::getPosition().x;
        int y = sf::Mouse::getPosition().y;
        Pressed = this->boundingBox.contains(x,y);
    }
    if(!this->wasPressed && Pressed) {
        this->wasPressed = Pressed;
        return true;
    }
    this->wasPressed = Pressed;
    return false;
}

void Button::setBoundingBox(const sf::IntRect &box) {
    this->boundingBox = box;
}

sf::RectangleShape &Button::getIcon() {
    return this->icon;
}

void Button::draw(sf::RenderWindow &window) {
    window.draw(this->getRectangleShape());
    window.draw(this->getIcon());
}
