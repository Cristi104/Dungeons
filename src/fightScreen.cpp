#include "../include/fightScreen.h"

FightScreen::FightScreen() {
    this->entities = new Entity*[8];
    for(int i = 0; i < 8; i++)
        this->entities[i] = nullptr;
    this->fightPanel = Panel();
    Component backGround;
    backGround.getRectangleShape().setPosition(0, 600.0f * Settings::getScaleHeight());
    backGround.getRectangleShape().setTexture(GameWindow::getTexture("PanelBackGround"));
    backGround.getRectangleShape().setSize(sf::Vector2f((float)Settings::getResolutionWidth(), 180 * Settings::getScaleHeight()));
    fightPanel.addComponent(backGround);
}

FightScreen::~FightScreen() {
    for(int i = 0; i < 8; i++)
        if(this->entities[i] != nullptr)
            delete this->entities[i];
    delete[] this->entities;
}

int FightScreen::getIndex(Positions position) {
    int x = static_cast<int>(position);
    int i;
    for(i = 0; x != 1; i++)x /= 2;
    return i;
}

sf::Vector2f FightScreen::getCoordsOfIndex(int index) {
    sf::Vector2f position;
    position.y = 200 * Settings::getScaleHeight();
    if(index < 4){
        position.x = (float)(210 + 90 * index) * Settings::getScaleWidth();
    } else {
        position.x = (float)(290 + 90 * index) * Settings::getScaleWidth();
    }
    return position;
}

void FightScreen::addEntity(const Entity &entity) {
    int index = FightScreen::getIndex(entity.getPosition());
    (*this->entities[index]) = entity;
}

void FightScreen::swapEntities(Positions position1, Positions position2) {
    int i1 = FightScreen::getIndex(position1);
    int i2 = FightScreen::getIndex(position2);
    this->swapEntities(i1, i2);
}

void FightScreen::swapEntities(int index1, int index2) {
    Entity* p = this->entities[index1];
    this->entities[index1] = this->entities[index2];
    this->entities[index2] = p;
    entities[index1]->getRectangleShape().setPosition(FightScreen::getCoordsOfIndex(index1));
    entities[index2]->getRectangleShape().setPosition(FightScreen::getCoordsOfIndex(index2));
}

void FightScreen::deleteEntity(Positions position) {
    int i = FightScreen::getIndex(position);
    delete this->entities[i];
    this->entities[i] = nullptr;
    if(i < 4){
        for(int j = 0; j < i - 1; j++)
            this->swapEntities(j,j + 1);
    } else {
        for(int j = 7; j > i + 1; j--)
            this->swapEntities(j,j - 1);
    }
}

void FightScreen::draw(sf::RenderWindow &window) {
    for(int i = 0; i < 8; i++)
        if(entities[i] != nullptr)
            window.draw(entities[i]->getRectangleShape());
    fightPanel.draw(window);
}
