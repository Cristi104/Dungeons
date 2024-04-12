#include <random>
#include "../../include/Map/Room.h"
#include "../../include/Map/BadMapGeneration.h"

Room::Room(MapEvent event) {
    this->event = event;
}

Room::Room(const Biome& biome) {
    std::random_device device;
    std::mt19937 gen(device());
    std::uniform_int_distribution<> random(1,100);
    this->event = MapEvent::NoEvent;
    if(random(gen) > biome.getRoomEventChance()) {
        return;
    }
    int helperEvent = 0;
    if(random(gen) > 80) {
        if (random(gen) > 70)
            helperEvent |= MapEvent::FightSmall;
        else
            helperEvent |= MapEvent::FightBig;
    }
    if (random(gen) > 50)
        helperEvent |= MapEvent::LootSmall;
    else
        helperEvent |= MapEvent::LootBig;
    this->event = static_cast<MapEvent>(helperEvent);
}

MapEvent Room::getEvent() {
    return this->event;
}

void Room::clear() {
    this->event = MapEvent::NoEvent;
}






