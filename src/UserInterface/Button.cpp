#include "../../include/UserInterface/Button.h"

Button::Button(int priority) : Component(priority) {
    this->boundingBox = sf::FloatRect (0,0,50,50);
    this->wasPressed = false;
}

bool Button::isPressed() {
    if(this->wasPressed){
        this->wasPressed = false;
        return true;
    }
    return false;
}

void Button::setBoundingBox(const sf::FloatRect &box) {
    this->boundingBox = box;
}

void Button::draw(sf::RenderWindow &window) {
    window.draw(this->getRectangleShape());
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

void Button::addPos(float x, float y) {
    Component::addPos(x, y);
    this->boundingBox.left += x;
    this->boundingBox.top += y;
}

