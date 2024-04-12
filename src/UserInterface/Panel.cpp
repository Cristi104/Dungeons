#include <iostream>
#include <SFML/Graphics/Sprite.hpp>
#include "../../include/UserInterface/Panel.h"

Panel::Panel() {
    this->isShown = false;
}

void Panel::draw(sf::RenderWindow &window) {
    if(!this->isShown)
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
    this->isShown ^= true;
}

Component* Panel::getComponent(int index) {
    try{
        return this->components.at(index);
    }catch(std::out_of_range&){
        std::cout << "Failed to get component, index out of range\n";
        return this->components[0];
    }
}

Panel::~Panel() {
    for(Component* component : this->components){
        delete component;
    }
}

bool Panel::handleEvent(const sf::Event &event) {
    if(!this->isShown)
        return false;
    for(Component* p : this->components){
        try{
            if(dynamic_cast<Button*>(p)->handleEvent(event))
                return true;
        }catch(std::bad_cast&){}
    }
    return false;
}
