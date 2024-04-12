#ifndef OOP_MAP_H
#define OOP_MAP_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Room.h"
#include "Biome.h"
#include "../UserInterface/Panel.h"

//class Map {
//private:
//    Room* startRoom;
//    sf::RenderTexture texture;
//    sf::RectangleShape sprite;
//    Panel panel;
//    static Room* extend(const Biome& biome, Room* room, int length = 1);
////    static void searchSize(Room* room, int currentX, int currentY, sf::IntRect& rect);
//public:
//    explicit Map(const Biome& biome = Biome());
//
//    void draw(sf::RenderWindow& window);
//
//    Room* getStartRoom() const;
//};

class Map{
private:
    struct nod{
        Road* roads[4] = {nullptr, nullptr, nullptr, nullptr};
        Room* room = nullptr;
    }** map;
    sf::Vector2i size;
    sf::RenderTexture texture;
    sf::RectangleShape sprite;
    sf::Vector2i extend(const Biome& biome, sf::Vector2i position, int length = 1);
public:
    explicit Map(const Biome& biome = Biome());

    ~Map();

    sf::RectangleShape &getSprite();
};

#endif //OOP_MAP_H
