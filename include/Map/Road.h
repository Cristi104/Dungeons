#ifndef OOP_ROAD_H
#define OOP_ROAD_H

#include "MapEvent.h"
#include "Biome.h"

class Road {
private:
    int length;
    int currentLengthPassed;
    int eventChance;
    bool hasBeenPassed;
public:

    /// creates a road according to default biome settings
    /// @param biome template biome
    explicit Road(const Biome& biome = Biome());

    /// increments through the road
    /// @return MapEvent of each passed cell
    MapEvent pass();

    bool getHasBeenPassed() const;
};


#endif //OOP_ROAD_H
