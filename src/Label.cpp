#include "../include/Label.h"
#include <cstring>
#include <iostream>

sf::Font Label::font;

void Label::setText(const std::string &string, const int maxLength) {
    char* copy = new char[string.size() + 1];
    strcpy(copy, string.c_str());
    char* splitText = new char[string.size() + 1];
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

void Label::initFont() {
    if (!Label::font.loadFromFile("../res/fonts/8bitOperatorPlus8-Regular.ttf"))
        std::cout << "Failed to load font.\n";
}

Label::Label() {
    this->text.setFont(Label::font);
    this->text.setCharacterSize(12);
    this->setPriority(2);
}

Label::Label(const std::string& text, int maxLength) {
    this->text.setFont(Label::font);
    this->text.setCharacterSize(12);
    this->setPriority(2);
    this->setText(text, maxLength);
}

void Label::draw(sf::RenderWindow &window) {
    window.draw(this->getRectangleShape());
    window.draw(this->text);
}
