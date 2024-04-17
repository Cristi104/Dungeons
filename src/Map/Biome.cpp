#include "../../include/Map/Biome.h"

Biome::Biome() {
    this->lengthMin = 5;
    this->lengthMax = 8;
    this->roomEventChance = 50;
    this->branchingChance = 40;
    this->roadLengthMin = 3;
    this->roadLengthMax = 6;
    this->roadEventChance = 20;
    this->size = sf::Vector2i(11,5);
}

int Biome::getLengthMin() const {
    return lengthMin;
}

int Biome::getLengthMax() const {
    return lengthMax;
}

int Biome::getRoomEventChance() const {
    return roomEventChance;
}

int Biome::getBranchingChance() const {
    return branchingChance;
}

int Biome::getRoadLengthMin() const {
    return roadLengthMin;
}

int Biome::getRoadLengthMax() const {
    return roadLengthMax;
}

int Biome::getRoadEventChance() const {
    return roadEventChance;
}

std::ostream &operator<<(std::ostream &out, const Biome &biome) {
    out << biome.lengthMin << ' '
        << biome.lengthMax << ' '
        << biome.roomEventChance << ' '
        << biome.branchingChance << ' '
        << biome.roadLengthMin << ' '
        << biome.roadLengthMax << ' '
        << biome.roadEventChance << ' '
        << biome.size.x << ' '
        << biome.size.y << '\n';
    return out;
}

std::istream &operator>>(std::istream &in, Biome &biome) {
    in >> biome.lengthMin
       >> biome.lengthMax
       >> biome.roadEventChance
       >> biome.branchingChance
       >> biome.roadLengthMin
       >> biome.roadLengthMax
       >> biome.roadEventChance
       >> biome.size.x
       >> biome.size.y;
    return in;
}

const sf::Vector2i &Biome::getSize() const {
    return size;
}
