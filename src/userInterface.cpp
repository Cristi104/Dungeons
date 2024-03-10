#include "../include/userInterface.h"

Component::Component() {
    this->priority = 0;
}

sf::Sprite &Component::getSprite() {
    return this->sprite;
}

void Component::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

void Component::setPriority(int priority_p) {
    this->priority = priority_p;
}

int Component::getPriority() const {
    return priority;
}

