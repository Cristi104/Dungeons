#include <iostream>
#include "../include/Panel.h"

Panel::Panel() {
    this->isShown = false;
    this->components.emplace_back();
    this->buttons.emplace_back();
    this->buttons[0].setBoundingBox(sf::IntRect(0,0,0,0));
    this->components.emplace_back();
}

void Panel::draw(sf::RenderWindow &window) {
    if(!this->isShown)
        return;
    for(int i = 0; i <= 5; i++) {
        for (Component &component: this->components) {
            if (component.getPriority() == i)
                component.draw(window);
        }
        for (Button &button: this->buttons) {
            if (button.getPriority() == i)
                button.draw(window);
        }
        for (Label &label: this->labels) {
            if (label.getPriority() == i)
                label.draw(window);
        }
    }
}

void Panel::addComponent(const Component& component) {
    this->components.push_back(component);
}

void Panel::addButton(const Button& button) {
    this->buttons.push_back(button);
}

void Panel::addLabel(const Label &label) {
    this->labels.push_back(label);
}

void Panel::toggleVisibility() {
    this->isShown ^= true;
}

Component& Panel::getComponent(int index) {
    try{
        return this->components.at(index);
    }catch(std::out_of_range&){
        std::cout << "Failed to get component, index out of range\n";
        return this->components[0];
    }
}

Button &Panel::getButton(int index) {
    try{
        return this->buttons.at(index);
    }catch(std::out_of_range&){
        std::cout << "Failed to get button, index out of range\n";
        return this->buttons[0];
    }
}

Label &Panel::getLabel(int index) {
    try{
        return this->labels.at(index);
    }catch(std::out_of_range&){
        std::cout << "Failed to get button, index out of range\n";
        return this->labels[0];
    }
}