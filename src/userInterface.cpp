#include <iostream>
#include <cstring>
#include "../include/userInterface.h"

//Component
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

//Label
sf::Font Label::font;

void Label::initFont() {
    if (!Label::font.loadFromFile("../res/fonts/8bitOperatorPlus8-Regular.ttf"))
        std::cout << "Failed to load font.\n";
}

Label::Label() {
    this->text.setFont(Label::font);
    this->text.setCharacterSize(12);
}

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

void Label::draw(sf::RenderWindow &window) {
    window.draw(this->getSprite());
    window.draw(this->text);
}

//Button
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

sf::Sprite &Button::getIcon() {
    return this->icon;
}

void Button::draw(sf::RenderWindow &window_p) {
    window_p.draw(this->getSprite());
    window_p.draw(this->icon);
}


