//
// Created by cristi on 16.05.2024.
//

#include "../../include/Entity/EntityFactory.h"
#include "../../include/Entity/Entities/Knight.h"
#include "../../include/Entity/Entities/Rogue.h"
#include "../../include/Entity/Entities/Skeleton.h"

Entity *EntityFactory::createEntity(int id) {
    switch (id) {
        case 0:
            return new Knight;
        case 1:
            return new Rogue;
        case 2:
            return new Skeleton;
        default:
            return nullptr;
    }
}
