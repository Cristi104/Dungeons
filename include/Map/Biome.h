#ifndef OOP_BIOME_H
#define OOP_BIOME_H


#include <ostream>
#include <istream>
#include <SFML/System/Vector2.hpp>

class Biome {
private:
    int lengthMin;
    int lengthMax;
    int roomEventChance;
    int branchingChance;
    int roadLengthMin;
    int roadLengthMax;
    int roadEventChance;
    sf::Vector2i size;
public:

    /// creates a biome object
    /// should only be used as a base
    Biome();

    /// serializes the biome data
    friend std::ostream& operator<<(std::ostream& out, const Biome& biome);

    /// deserializes the biome data
    /// this should be used for custom biome creation
    friend std::istream& operator>>(std::istream& in, Biome& biome);

    int getLengthMin() const;
    int getLengthMax() const;
    int getRoomEventChance() const;
    int getBranchingChance() const;
    int getRoadLengthMin() const;
    int getRoadLengthMax() const;
    int getRoadEventChance() const;
    const sf::Vector2i& getSize() const;

};


#endif //OOP_BIOME_H
