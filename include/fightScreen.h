#ifndef OOP_FIGHTSCREEN_H
#define OOP_FIGHTSCREEN_H

#include "../include/entity.h"
#include "../include/userInterface.h"
#include "../include/window.h"

class FightScreen {
private:
    Entity** entities;
    Panel fightPanel;
    static int getIndex(Positions position);
    static sf::Vector2f getCoordsOfIndex(int index);
public:
    FightScreen();
    ~FightScreen();
    void addEntity(const Entity& entity);
    void swapEntities(Positions position1, Positions position2);
    void swapEntities(int index1, int index2);
    void deleteEntity(Positions position);
    void draw(sf::RenderWindow& window);
};

#endif //OOP_FIGHTSCREEN_H
