#include "../../include/Graphics/GameWindow.h"
#include <filesystem>
#include <iostream>
#include "../../include/Graphics/MissingTexture.h"

std::map<const std::string, sf::Texture*> GameWindow::textures;

GameWindow::GameWindow() {
    this->window.create(sf::VideoMode(1200, 720), "Hello World", sf::Style::Default);
    GameWindow::loadTextures("../res/assets");
    this->window.setFramerateLimit(60);
}

GameWindow::GameWindow(const std::string &name, int x, int y) {
    this->window.create(sf::VideoMode(x, y), name, sf::Style::Fullscreen);
    GameWindow::loadTextures("../res/assets");
    this->window.setFramerateLimit(60);
}

GameWindow::~GameWindow(){
    this->window.close();
}

void GameWindow::loadTextures(const std::string &path) {
    for(const auto& file : std::filesystem::directory_iterator(path)) {
        std::string filePath = file.path().string();
        if(filePath.rfind(".png") != filePath.size() - 4)
            continue;
        auto* texture = new sf::Texture;
        std::string textureName;
        if(!texture->loadFromFile(filePath)) {
            delete texture;
            std::cout<< "Failed to load texture at " << filePath << '\n';
        } else {
//            texture->setSmooth(true);
            textureName = filePath.substr(path.size() + 1, filePath.size()- path.size() - 1 - 4);
            GameWindow::textures.insert(std::pair<const std::string, sf::Texture*>(textureName, texture));
        }
    }
}

const sf::Texture* GameWindow::getTexture(const std::string &name) {
    try {
        return GameWindow::textures.at(name);
    }catch(std::out_of_range&){
        throw MissingTexture("Missing texture at: ../res/assets/" + name + "\n");
    }
}

void GameWindow::freeTextures() {
    for(std::pair<const std::string&, sf::Texture*> pair : GameWindow::textures){
        delete pair.second;
    }
}

sf::RenderWindow& GameWindow::getWindow() {
    return window;
}