#include "../include/window.h"
#include <filesystem>
#include <iostream>
GameWindow::GameWindow() {
    this->window.create(sf::VideoMode(1200, 720), "Hello World");
    this->loadTextures("../res/assets");
}

GameWindow::GameWindow(const std::string &name_p, int x_p, int y_p) {
    this->window.create(sf::VideoMode(x_p, y_p), name_p);
    this->loadTextures("../res/assets");
}

void GameWindow::loadTextures(const std::string &path_p) {
    for(const auto& file : std::filesystem::directory_iterator(path_p)) {
        std::string filePath = file.path().string();
        if(filePath.rfind(".png") != filePath.size() - 4)
            continue;
        sf::Texture texture;
        std::string textureName;
        if(!texture.loadFromFile(filePath)) {
            std::cout<< "Failed to load texture at " << filePath << '\n';
        } else {
            textureName = filePath.substr(path_p.size() + 1, filePath.size()- path_p.size() - 1 - 4);
            textures.insert(std::pair<const std::string, sf::Texture>(textureName, texture));
        }
    }
}

const sf::Texture& GameWindow::getTexture(const std::string &name_p) {
    return textures.at(name_p);
}
