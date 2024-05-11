#include "../../include/UserInterface/Component.h"

Component::Component(int priority) {
    this->priority = priority;
}

sf::RectangleShape &Component::getRectangleShape() {
    return this->sprite;
}

void Component::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

void Component::setPriority(int value) {
    this->priority = value;
}

int Component::getPriority() const {
    return priority;
}

void Component::addPos(float x, float y) {
    this->sprite.setPosition(this->sprite.getPosition() + sf::Vector2f(x,y));
}