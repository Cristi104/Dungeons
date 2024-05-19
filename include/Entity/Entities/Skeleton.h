//
// Created by cristi on 16.05.2024.
//

#ifndef OOP_SKELETON_H
#define OOP_SKELETON_H


#include "../Entity.h"
#include "../EnemyAI.h"

class Skeleton : public Entity , public EnemyAI{

public:
    Skeleton();

    sf::Vector2i getAttack(Entity** fight) override;
};


#endif //OOP_SKELETON_H
