#include "../../include/UserInterface/Button.h"

Button::Button() {
    this->setPriority(5);
    this->boundingBox = sf::IntRect(0,0,50,50);
    this->wasPressed = false;
}

bool Button::isPressed() {
    if(this->wasPressed){
        this->wasPressed = false;
        return true;
    }
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

bool Button::handleEvent(const sf::Event &event) {
    if(event.type == sf::Event::MouseButtonPressed){
        int x = sf::Mouse::getPosition().x;
        int y = sf::Mouse::getPosition().y;
        if(this->boundingBox.contains(x,y)){
            this->wasPressed = true;
            return true;
        }
    }
    return false;
}
