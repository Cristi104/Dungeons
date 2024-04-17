#include "../../include/UserInterface/PopupPanel.h"

PopupPanel::PopupPanel() : Button(){
}

void PopupPanel::draw(sf::RenderWindow &window) {
    Button::draw(window);
    this->panel.draw(window);
}

bool PopupPanel::handleEvent(const sf::Event &event) {
    if(event.type != sf::Event::MouseMoved)
        return false;
    int x = sf::Mouse::getPosition().x;
    int y = sf::Mouse::getPosition().y;
    if(this->boundingBox.contains(x,y)){
        if(!this->panel.isVisible()){
            this->panel.toggleVisibility();
            this->setPriority(this->getPriority() + 1);
        }
        return false;
    }
    if(this->panel.isVisible()){
        this->panel.toggleVisibility();
        this->setPriority(this->getPriority() - 1);
    }
    return false;
}

int PopupPanel::addComponent(Component *component) {
    return this->panel.addComponent(component);
}

void PopupPanel::addPosition(sf::Vector2f position) {
    Button::addPosition(position);
    this->panel.addPosition(position);
}

