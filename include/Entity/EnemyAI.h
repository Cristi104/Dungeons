#ifndef OOP_ENEMYAI_H
#define OOP_ENEMYAI_H

#include "Entity.h"

class EnemyAI {
private:

    void update(Entity** fight, int currentPosition);

protected:
    float aggressiveness;
public:

    EnemyAI();

    virtual sf::Vector2i getAttack(Entity** fight) = 0;
};


#endif //OOP_ENEMYAI_H
