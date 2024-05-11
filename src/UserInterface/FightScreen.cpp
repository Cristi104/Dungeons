#include <iostream>
#include <valarray>
#include <thread>
#include "../../include/UserInterface/FightScreen.h"
#include "../../include/UserInterface/PopupPanel.h"
#include "../../include/UserInterface/Border.h"
#include "../../include/UserInterface/MovePopup.h"
#include "../../include/UserInterface/MapPanel.h"
#include "../../include/UserInterface/CharacterPanel.h"

FightScreen* FightScreen::singleton = nullptr;

FightScreen::FightScreen() :Panel() {
    this->selectedEntity = 3;
    this->selectedMove = 0;
    this->entities = new Entity*[8];
    for(int i = 0; i < 8; i++)
        this->entities[i] = nullptr;
    for(int i = 0; i < 8; i++){
        auto* button = new Button;
        sf::Vector2f position = FightScreen::getCoordsOfIndex(i);
        button->setBoundingBox({position.x,
                                position.y,
                                120 * Settings::getInstance()->getScaleWidth(),
                                200 * Settings::getInstance()->getScaleHeight()});
        this->addComponent(button);
    }
    this->characterPanel = new CharacterPanel*[4];
    for(int i = 0; i < 4; i++)this->characterPanel[i] = nullptr;
    this->currentMap = new Map;
    this->mapPanel = new MapPanel(this->currentMap);
    this->mapPanel->toggleVisibility();
    this->toggleVisibility();
}

FightScreen::~FightScreen() {
    for(int i = 0; i < 8; i++)
        if(this->entities[i] != nullptr)
            delete this->entities[i];
    delete[] this->entities;
    delete this->characterPanel;
    delete this->mapPanel;
    delete this->currentMap;
}

int FightScreen::getIndex(Positions position) {
    int x = static_cast<int>(position);
    int i;
    for(i = 0; x != 1; i++)x /= 2;
    return i;
}

sf::Vector2f FightScreen::getCoordsOfIndex(int index) {
    sf::Vector2f position;
    position.y = 200 * Settings::getInstance()->getScaleHeight();
    if(index < 4){
        position.x = (float)(50 + 130 * index) * Settings::getInstance()->getScaleWidth();
    } else {
        position.x = (float)(130 + 130 * index) * Settings::getInstance()->getScaleWidth();
    }
    return position;
}

void FightScreen::addEntity(Entity* entity) {
    int index = FightScreen::getIndex(entity->getPosition());
    this->entities[index] = entity;
    if(index < 4)
        this->characterPanel[index] = new CharacterPanel(entity);
    entity->getRectangleShape().setPosition(FightScreen::getCoordsOfIndex(index));
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
    if(index1 < 4 && index2 < 4){
        auto* aux = this->characterPanel[index2];
        this->characterPanel[index2] = this->characterPanel[index1];
        this->characterPanel[index1] = aux;
    }
    if(this->entities[index1])
        this->entities[index1]->getRectangleShape().setPosition(FightScreen::getCoordsOfIndex(index1));
    if(this->entities[index2])
        this->entities[index2]->getRectangleShape().setPosition(FightScreen::getCoordsOfIndex(index2));
}

void FightScreen::deleteEntity(Positions position) {
    int i = FightScreen::getIndex(position);
    this->deleteEntity(i);
}

void FightScreen::deleteEntity(int index) {
    delete this->entities[index];
    this->entities[index] = nullptr;
    if(index < 4){
        for(int j = 0; j < index - 1; j++)
            this->swapEntities(j,j + 1);
    } else {
        for(int j = 7; j > index + 1; j--)
            this->swapEntities(j,j - 1);
    }
}

void FightScreen::draw(sf::RenderWindow &window) {
    for(int i = 0; i < 8; i++)
        if(entities[i] != nullptr){
            entities[i]->getRectangleShape().setPosition(FightScreen::getCoordsOfIndex(i));
            window.draw(entities[i]->getRectangleShape());
        }
    Panel::draw(window);
    this->mapPanel->draw(window);
    if(this->characterPanel[this->selectedEntity])
        this->characterPanel[this->selectedEntity]->draw(window);
}

FightScreen *FightScreen::getInstance() {
    if(FightScreen::singleton == nullptr)
        FightScreen::singleton = new FightScreen;
    return FightScreen::singleton;
}

bool FightScreen::handleEvent(const sf::Event &event) {
    if(this->characterPanel[this->selectedEntity])
        if(this->characterPanel[this->selectedEntity]->handleEvent(event))
            return true;
    if(this->mapPanel->handleEvent(event))
        return true;
    if(!this->visible)
        return false;
    if(turnOrder.top() >= 4)
        return false;
    if(event.type == sf::Event::KeyPressed){
//        std::cout<<"miscare\n";
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) &&
           (FightScreen::getPosition(turnOrder.top()) &
            this->entities[turnOrder.top()]->getMoves()[0].getCastPosition())){
            this->selectedMove = 1;
            return true;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) &&
           (FightScreen::getPosition(turnOrder.top()) &
            this->entities[turnOrder.top()]->getMoves()[1].getCastPosition())){
            this->selectedMove = 2;
            return true;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) &&
           (FightScreen::getPosition(turnOrder.top()) &
            this->entities[turnOrder.top()]->getMoves()[2].getCastPosition())){
            this->selectedMove = 3;
            return true;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) &&
           (FightScreen::getPosition(turnOrder.top()) &
            this->entities[turnOrder.top()]->getMoves()[3].getCastPosition())){
            this->selectedMove = 4;
            return true;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)){
            this->selectedMove = 5;
            return true;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)){
            std::cout << "end turn\n";
            this->endEntityTurn();
            return true;
        }
    }
    if(event.type == sf::Event::MouseButtonPressed){
        if(this->selectedMove == 0)
            return false;
        Move* move;
        if(this->selectedMove < 5){
            move = &this->entities[this->turnOrder.top()]->getMoves()[this->selectedMove - 1];
            for (int i = 0; i < 8; i++) {
                EventHandler* handler = dynamic_cast<Button *>(this->components[i]);
                if(!handler)
                    continue;
                if (!handler->handleEvent(event))
                    continue;
                if (!(move->getRange() & getPosition(i)))
                    continue;
                if(move->isAoe()){
                    for(int j = 0; j < 8; j++){
                        if(FightScreen::getPosition(j) & move->getRange()){
                            this->entities[j]->getHit(*move);
                        }
                    }
                } else
                    this->entities[i]->getHit(*move);
                this->endEntityTurn();
                return true;
            }
        } else {
            for(int i = 0; i < 4; i++){
                if(i == turnOrder.top())
                    continue;
                try{
                    if(!dynamic_cast<Button*>(this->components[i])->handleEvent(event))
                        continue;
                    this->swapEntities(i, this->turnOrder.top());
                    return true;
                }catch(std::bad_cast&){}
            }
        }
    }
    return false;
}

void FightScreen::turn() {
    if(this->turnOrder.empty()){
        std::cout << "new turn\n";
        for(int i = 0; this->turnOrder.size() != 8; i++){
            for(int j = 0; j < 8; j++){
                if(this->entities[j] == nullptr)
                    continue;
                if(this->entities[j]->getStats().getValue(EffectType::SPEED) == i){
                    this->turnOrder.push(j);
                }
            }
            if(i > 40)
                break;
        }
    }
}

void FightScreen::endEntityTurn() {
    this->turnOrder.pop();
    this->selectedMove = 0;
    this->turn();
    this->entities[turnOrder.top()]->turn();
    if(this->turnOrder.top() < 4){
        this->characterPanel[turnOrder.top()]->update();
    }
//    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

Positions FightScreen::getPosition(int index) {
    return static_cast<Positions>(pow(2,index));
}
