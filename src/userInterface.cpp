#include <iostream>
#include <cstring>
#include "../include/userInterface.h"

//Component
Component::Component() {
    this->priority = 0;
}

sf::RectangleShape &Component::getRectangleShape() {
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

//Label
sf::Font Label::font;

void Label::setText(const std::string &text_p, const int maxLength_p) {
    char* copy = new char[text_p.size() + 1];
    strcpy(copy, text_p.c_str());
    char* splitText = new char[text_p.size() + 1];
    char* p = strtok(copy, " ");
    int size = 0;
    while(p){
        if(size == 0 && (int)strlen(p) + 1 >= maxLength_p) {
            strcat(splitText, p);
            strcat(splitText, "\n");
            p = strtok(nullptr, " ");
            continue;
        }
        if(size + (int)strlen(p) + 1 >= maxLength_p) {
            splitText[strlen(splitText)-1] = '\n';
            size = 0;
        }
        size += (int)strlen(p) + 1;
        strcat(splitText, p);
        strcat(splitText, " ");
        p = strtok(nullptr, " ");
    }
    this->text.setString(splitText);
    delete[] splitText;
    delete[] copy;
}

void Label::initFont() {
    if (!Label::font.loadFromFile("../res/fonts/8bitOperatorPlus8-Regular.ttf"))
        std::cout << "Failed to load font.\n";
}

Label::Label() {
    this->text.setFont(Label::font);
    this->text.setCharacterSize(12);
    this->setPriority(9);
}

Label::Label(const std::string& text_p, int maxLength_p) {
    this->text.setFont(Label::font);
    this->text.setCharacterSize(12);
    this->setPriority(9);
    this->setText(text_p, maxLength_p);
}

void Label::draw(sf::RenderWindow &window) {
    window.draw(this->getRectangleShape());
    window.draw(this->text);
}

//Button
Button::Button() {
    this->setPriority(5);
    this->boundingBox = sf::IntRect(0,0,50,50);
}

bool Button::isPressed() {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        int x = sf::Mouse::getPosition().x;
        int y = sf::Mouse::getPosition().y;
        return this->boundingBox.contains(x,y);
    }
    return false;
}

void Button::setBoundingBox(const sf::IntRect &boundingBox_p) {
    this->boundingBox = boundingBox_p;
}

sf::RectangleShape &Button::getIcon() {
    return this->icon;
}

void Button::draw(sf::RenderWindow &window_p) {
    window_p.draw(this->getRectangleShape());
    window_p.draw(this->getIcon());
}

//Panel
Panel::Panel() {
    this->isShown = false;
    this->components.emplace_back();
    this->buttons.emplace_back();
    this->buttons[0].setBoundingBox(sf::IntRect(0,0,0,0));
}

void Panel::draw(sf::RenderWindow &window_p) {
    if(!this->isShown)
        return;
    for(int i = 0; i <= 5; i++){
        for(Component& component : this->components){
            if(component.getPriority() == i)
                component.draw(window_p);
        }
    }
    for(int i = 0; i <= 5; i++){
        for(Button& button : this->buttons){
            if(button.getPriority() == i)
                button.draw(window_p);
        }
    }
    for(int i = 6; i <= 9; i++){
        for(Component& component : this->components){
            if(component.getPriority() == i)
                component.draw(window_p);
        }
    }
}

void Panel::addComponent(const Component& component_p) {
    this->components.push_back(component_p);
}

void Panel::addButton(const Button& button_p) {
    this->buttons.push_back(button_p);
}

void Panel::toggleVisibility() {
    this->isShown ^= true;
}

Component& Panel::getComponent(int index_p) {
    try{
        return this->components.at(index_p);
    }catch(std::out_of_range&){
        std::cout << "Failed to get component, index out of range\n";
        return this->components[0];
    }
}

Button &Panel::getButton(int index_p) {
    try{
        return this->buttons.at(index_p);
    }catch(std::out_of_range&){
        std::cout << "Failed to get button, index out of range\n";
        return this->buttons[0];
    }
}