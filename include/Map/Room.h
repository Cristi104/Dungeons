#ifndef OOP_ROOM_H
#define OOP_ROOM_H

#include "Road.h"
#include "Biome.h"

class Room {
private:
    MapEvent event;

public:

    /// creates a room according to default biome settings
    /// @param biome template biome
    explicit Room(const Biome& biome = Biome());

    /// creates a room with a specific MapEvent
    explicit Room(MapEvent event);

    /// sets the MapEvent to None
    /// should be called when the room is cleared to remove repeat clearing
    void clear();

    MapEvent getEvent();
};


#endif //OOP_ROOM_H
