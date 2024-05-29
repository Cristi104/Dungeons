#include "../../include/Entity/AllyFactory.h"
#include "../../include/Entity/Entities/Knight.h"
#include "../../include/Entity/Entities/Rogue.h"

Entity *AllyFactory::createEntity(int id) {
    switch (id) {
        case 0:
            return new Knight;
        case 1:
            return new Rogue;
        default:
            return nullptr;
    }
}
