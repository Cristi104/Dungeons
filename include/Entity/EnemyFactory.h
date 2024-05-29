#ifndef OOP_ENEMYFACTORY_H
#define OOP_ENEMYFACTORY_H


#include "EntityFactory.h"

class EnemyFactory : public EntityFactory{
public:
    Entity * createEntity(int id) override;
};


#endif //OOP_ENEMYFACTORY_H
