#ifndef OOP_MAPPANEL_H
#define OOP_MAPPANEL_H

#include "Panel.h"
#include "../../Map/Map.h"

class MapPanel : public Panel{
private:
    sf::Vector2i size;
    sf::Vector2i CurrentPosition;
    sf::RectangleShape Pointer;
    Map* map;

public:
    explicit MapPanel(Map* map);

    void draw(sf::RenderWindow& window) override;
};

#endif //OOP_MAPPANEL_H
