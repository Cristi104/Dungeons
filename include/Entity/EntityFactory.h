//
// Created by cristi on 16.05.2024.
//

#ifndef OOP_ENTITYFACTORY_H
#define OOP_ENTITYFACTORY_H


#include "Entity.h"

class EntityFactory {
public:
    Entity* createEntity(int id);
};


#endif //OOP_ENTITYFACTORY_H
