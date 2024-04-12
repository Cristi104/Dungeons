#include <random>
#include "../../include/Map/Road.h"

Road::Road(const Biome &biome) {
    this->eventChance = biome.getRoadEventChance();
    this->hasBeenPassed = false;
    this->currentLengthPassed = 0;
    std::random_device device;
    std::mt19937 gen(device());
    std::uniform_int_distribution<> random(1,100);
    this->length = biome.getRoadLengthMin() + random(gen) % (biome.getRoadLengthMax() - biome.getRoadLengthMin());
}

MapEvent Road::pass() {
    std::random_device device;
    std::mt19937 gen(device());
    std::uniform_int_distribution<> random(1,100);
    if(this->currentLengthPassed == this->length)
        this->hasBeenPassed = true;
    this->currentLengthPassed++;
    if(random(gen) > this->eventChance || this->hasBeenPassed)
        return MapEvent::NoEvent;
    if(random(gen) > 30) {
        if (random(gen) > 10)
            return MapEvent::FightSmall;
        return MapEvent::FightBig;
    } else {
        if (random(gen) > 10)
            return MapEvent::LootSmall;
        return MapEvent::LootBig;
    }
}

bool Road::getHasBeenPassed() const {
    return hasBeenPassed;
}
