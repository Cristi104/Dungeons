#include "../include/Component.h"

Component::Component() {
    this->priority = 0;
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
