//
// Created by cristi on 26.05.2024.
//

#ifndef OOP_SPEARMAN_H
#define OOP_SPEARMAN_H


#include "../Entity.h"
#include "../EnemyAI.h"

class Spearman : public Entity , public EnemyAI{
public:
    Spearman();
    sf::Vector2i getAttack(Entity** fight) override;

};


#endif //OOP_SPEARMAN_H
