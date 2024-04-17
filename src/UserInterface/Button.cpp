#include "../../include/UserInterface/Button.h"

Button::Button(int priority) : Component(priority) {
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

void Button::addPosition(sf::Vector2f position) {
    Component::addPosition(position);
    this->icon.setPosition(this->icon.getPosition() + position);
    this->boundingBox.left += (int)position.x;
    this->boundingBox.top += (int)position.y;
}
