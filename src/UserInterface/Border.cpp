#include <iostream>
#include <SFML/Graphics/Sprite.hpp>
#include "../../include/UserInterface/Border.h"
#include "../../include/Graphics/window.h"

Border::Border() {
    sf::IntRect rect(0,0,128,128);
    if(!this->target.create((rect.width / 32) * 32, (rect.height / 32) * 32)){
        std::cout << "Failed to create RenderTexture.\n";
    }
    this->target.clear(sf::Color(11,16,22));
    sf::Sprite helperSprite;
    helperSprite.setTexture(*GameWindow::getTexture("borderCorner"));
    target.draw(helperSprite);
    helperSprite.setPosition((float)target.getSize().x, 0);
    helperSprite.rotate(90);
    target.draw(helperSprite);
    helperSprite.setPosition((float)target.getSize().x, (float)target.getSize().y);
    helperSprite.rotate(90);
    target.draw(helperSprite);
    helperSprite.setPosition(0, (float)target.getSize().y);
    helperSprite.rotate(90);
    target.draw(helperSprite);
    helperSprite.setTexture(*GameWindow::getTexture("border"));
    helperSprite.rotate(90);
    for(int i = 32; i < (int)this->target.getSize().x - 32; i += 32){
        helperSprite.setPosition((float)i, 0);
        target.draw(helperSprite);
    }
    helperSprite.rotate(90);
    for(int i = 32; i < (int)this->target.getSize().y - 32; i += 32){
        helperSprite.setPosition((float)target.getSize().x, (float)i);
        target.draw(helperSprite);
    }
    helperSprite.rotate(90);
    for(int i = 32; i < (int)this->target.getSize().x - 32; i += 32){
        helperSprite.setPosition((float)i + 32, (float)target.getSize().y);
        target.draw(helperSprite);
    }
    helperSprite.rotate(90);
    for(int i = 32; i < (int)this->target.getSize().y - 32; i += 32){
        helperSprite.setPosition(0, (float)i + 32);
        target.draw(helperSprite);
    }
    this->target.display();
    this->getRectangleShape().setTexture(&this->target.getTexture());
    this->getRectangleShape().setPosition((float)rect.left, (float)rect.top);
    this->getRectangleShape().setSize({(float)rect.width, (float)rect.height});
    this->setPriority(0);
}
//
//Border::Border(sf::IntRect rect, int scale) {
//    if(!this->target.create((rect.width / (32 * scale)) * (32 * scale), (rect.height / (32 * scale)) * (32 * scale))){
//        std::cout << "Failed to create RenderTexture.\n";
//    }
//    this->target.clear(sf::Color(11,16,22));
//    sf::Sprite sprite;
//    sprite.setScale((float)scale, (float)scale);
//    sprite.setTexture(*GameWindow::getTexture("borderCorner"));
//    target.draw(sprite);
//    sprite.setPosition((float)target.getSize().x, 0);
//    sprite.rotate(90);
//    target.draw(sprite);
//    sprite.setPosition((float)target.getSize().x, (float)target.getSize().y);
//    sprite.rotate(90);
//    target.draw(sprite);
//    sprite.setPosition(0, (float)target.getSize().y);
//    sprite.rotate(90);
//    target.draw(sprite);
//    sprite.setTexture(*GameWindow::getTexture("border"));
//    sprite.rotate(90);
//    for(int i = (32 * scale); i < (int)this->target.getSize().x - (32 * scale); i += (32 * scale)){
//        sprite.setPosition((float)i,0);
//        target.draw(sprite);
//    }
//    sprite.rotate(90);
//    for(int i = (32 * scale); i < (int)this->target.getSize().y - (32 * scale); i += (32 * scale)){
//        sprite.setPosition((float)target.getSize().x, (float)i);
//        target.draw(sprite);
//    }
//    sprite.rotate(90);
//    for(int i = (32 * scale); i < (int)this->target.getSize().x - (32 * scale); i += (32 * scale)){
//        sprite.setPosition((float)i + (float)(32 * scale),(float)target.getSize().y);
//        target.draw(sprite);
//    }
//    sprite.rotate(90);
//    for(int i = (32 * scale); i < (int)this->target.getSize().y - (32 * scale); i += (32 * scale)){
//        sprite.setPosition(0, (float)i + (float)(32 * scale));
//        target.draw(sprite);
//    }
//    this->target.display();
//    this->getRectangleShape().setTexture(&this->target.getTexture());
//    this->getRectangleShape().setPosition((float)rect.left, (float)rect.top);
//    this->getRectangleShape().setSize({(float)rect.width, (float)rect.height});
//    this->setPriority(0);
//}

Border::Border(sf::IntRect rect, int scale, const std::string& name) {
    if(!this->target.create((rect.width / (32 * scale)) * (32 * scale), (rect.height / (32 * scale)) * (32 * scale))){
        std::cout << "Failed to create RenderTexture.\n";
    }
    this->target.clear(sf::Color(11,16,22));
    sf::Sprite helperSprite;
    helperSprite.setScale((float)scale, (float)scale);
    helperSprite.setTexture(*GameWindow::getTexture(name + "Corner"));
    target.draw(helperSprite);
    helperSprite.setPosition((float)target.getSize().x, 0);
    helperSprite.rotate(90);
    target.draw(helperSprite);
    helperSprite.setPosition((float)target.getSize().x, (float)target.getSize().y);
    helperSprite.rotate(90);
    target.draw(helperSprite);
    helperSprite.setPosition(0, (float)target.getSize().y);
    helperSprite.rotate(90);
    target.draw(helperSprite);
    helperSprite.setTexture(*GameWindow::getTexture(name));
    helperSprite.rotate(90);
    for(int i = (32 * scale); i < (int)this->target.getSize().x - (32 * scale); i += (32 * scale)){
        helperSprite.setPosition((float)i, 0);
        target.draw(helperSprite);
    }
    helperSprite.rotate(90);
    for(int i = (32 * scale); i < (int)this->target.getSize().y - (32 * scale); i += (32 * scale)){
        helperSprite.setPosition((float)target.getSize().x, (float)i);
        target.draw(helperSprite);
    }
    helperSprite.rotate(90);
    for(int i = (32 * scale); i < (int)this->target.getSize().x - (32 * scale); i += (32 * scale)){
        helperSprite.setPosition((float)i + (float)(32 * scale), (float)target.getSize().y);
        target.draw(helperSprite);
    }
    helperSprite.rotate(90);
    for(int i = (32 * scale); i < (int)this->target.getSize().y - (32 * scale); i += (32 * scale)){
        helperSprite.setPosition(0, (float)i + (float)(32 * scale));
        target.draw(helperSprite);
    }
    this->target.display();
    this->getRectangleShape().setTexture(&this->target.getTexture());
    this->getRectangleShape().setPosition((float)rect.left, (float)rect.top);
    this->getRectangleShape().setSize({(float)rect.width, (float)rect.height});
    this->setPriority(0);
}


