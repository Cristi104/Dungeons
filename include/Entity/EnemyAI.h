#ifndef OOP_ENEMYAI_H
#define OOP_ENEMYAI_H

#include "Entity.h"

class EnemyAI {

protected:
    float aggressiveness;

    void update(Entity** fight, int currentPosition);

public:

    EnemyAI();

    virtual sf::Vector2i getAttack(Entity** fight) = 0;
};


#endif //OOP_ENEMYAI_H
