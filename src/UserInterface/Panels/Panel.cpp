#include <iostream>
#include <SFML/Graphics/Sprite.hpp>
#include "../../../include/UserInterface/Panels/Panel.h"

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

int Panel::handleEvent(const sf::Event &event) {
    if(!this->visible)
        return false;
    for(int i = 0; i < (int)this->components.size(); i++){
        auto* handler = dynamic_cast<Button*>(this->components[i]);
        if(!handler)
            continue;
        if(handler->handleEvent(event))
            return i;
    }
    return 0;
}

bool Panel::isVisible() const {
    return visible;
}

void Panel::addPos(float x, float y) {
    for(Component* p : this->components){
        p->addPosition<sf::Vector2f>({x,y});
    }
}

