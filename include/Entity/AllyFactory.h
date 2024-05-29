#ifndef OOP_ALLYFACTORY_H
#define OOP_ALLYFACTORY_H

#include "EntityFactory.h"

class AllyFactory : public EntityFactory{
public:
    Entity* createEntity(int id) override;
};


#endif //OOP_ALLYFACTORY_H
