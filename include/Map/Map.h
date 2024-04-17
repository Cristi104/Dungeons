#ifndef OOP_MAP_H
#define OOP_MAP_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Room.h"
#include "Biome.h"
#include "../UserInterface/Panel.h"

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

    /// creates a Map object based on a biome
    explicit Map(const Biome& biome = Biome());

    ~Map();

    const sf::RenderTexture &getTexture() const;

    sf::RectangleShape &getSprite();
};

#endif //OOP_MAP_H
