#include <iostream>
#include <SFML/Graphics/Sprite.hpp>
#include "../../include/UserInterface/Panel.h"

Panel::Panel() {
    this->visible = false;
}

void Panel::draw(sf::RenderWindow &window) {
    if(!this->visible)
        return;
    for(int i = 0; i <= 6; i++) {
        for (Component* component: this->components) {
            if (component->getPriority() == i)
                component->draw(window);
        }
    }
}

int Panel::addComponent(Component* component) {
    this->components.push_back(component);
    return (int)this->components.size() - 1;
}

void Panel::toggleVisibility() {
    this->visible ^= true;
}

Component* Panel::getComponent(int index) {
    try{
        return this->components.at(index);
    }catch(std::out_of_range&){
        std::cout << "Failed to getInstance component, index out of range\n";
        return this->components[0];
    }
}

Panel::~Panel() {
    for(Component* component : this->components){
        delete component;
    }
}

bool Panel::handleEvent(const sf::Event &event) {
    if(!this->visible)
        return false;
    for(Component* p : this->components){
        EventHandler* handler = dynamic_cast<Button*>(p);
        if(!handler)
            continue;
        if(handler->handleEvent(event))
            return true;
    }
    return false;
}

bool Panel::isVisible() const {
    return visible;
}

void Panel::addPosition(sf::Vector2f position) {
    for(Component* p : this->components){
        p->addPosition(position);
    }
}

