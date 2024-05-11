#include "../../include/UserInterface/Label.h"
#include "../../include/Graphics/Settings.h"
#include <cstring>
#include <iostream>

void Label::setText(const std::string &string, const int maxLength) {
    char* copy = new char[string.size() + 1];
    strcpy(copy, string.c_str());
    char* splitText = new char[string.size() + 2];
    splitText[0] = '\0';
    char* p = strtok(copy, " ");
    int size = 0;
    while(p){
        if(size == 0 && (int)strlen(p) + 1 >= maxLength) {
            strcat(splitText, p);
            strcat(splitText, "\n");
            p = strtok(nullptr, " ");
            continue;
        }
        if(size + (int)strlen(p) + 1 >= maxLength) {
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

Label::Label(int fontSize, int priority) : Component(priority){
    if (!this->font.loadFromFile("../res/fonts/8bitOperatorPlus8-Regular.ttf"))
        std::cout << "Failed to load font.\n";
    this->text.setFont(this->font);
    this->text.setCharacterSize((unsigned int)((float)fontSize * Settings::getInstance()->getScaleHeight()));
    this->text.setFillColor(sf::Color(62,64,100));
}

Label::Label(const std::string& text, int fontSize, int maxLength, int priority) : Component(priority){
    if (!this->font.loadFromFile("../res/fonts/8bitOperatorPlus8-Regular.ttf"))
        std::cout << "Failed to load font.\n";
    this->text.setFont(this->font);
    this->text.setCharacterSize((unsigned int)((float)fontSize * Settings::getInstance()->getScaleHeight()));
    this->setText(text, maxLength);
    this->text.setFillColor(sf::Color(62,64,100));
}

void Label::draw(sf::RenderWindow &window) {
    window.draw(this->getRectangleShape());
    window.draw(this->text);
}

void Label::setFormatedText(const std::string &string) {
    this->text.setString(string);
}

void Label::addPos(float x, float y) {
    Component::addPos(x, y);
    this->text.setPosition(this->text.getPosition() + sf::Vector2f(x,y));
}

sf::Text &Label::getText(){
    return text;
}
