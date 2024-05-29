#include "../../include/Entity/EnemyFactory.h"
#include "../../include/Entity/Entities/Skeleton.h"
#include "../../include/Entity/Entities/Spearman.h"

Entity *EnemyFactory::createEntity(int id) {
    switch (id) {
        case 0:
            return new Skeleton;
        case 1:
            return new Spearman;
        default:
            return nullptr;
    }
}
