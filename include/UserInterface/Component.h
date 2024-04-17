#ifndef OOP_COMPONENT_H
#define OOP_COMPONENT_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Drawn.h"
#include "Drawn.h"

class Component : public Drawn{
private:
    sf::RectangleShape sprite;
    int priority;

public:

    /// creates an empty component of priority 1
    explicit Component(int priority = 1);

    virtual ~Component() = default;

    sf::RectangleShape& getRectangleShape();

    void draw(sf::RenderWindow& window) override;

    void addPosition(sf::Vector2f position) override;

    /// sets the draw order priority 0 - first, 5 - last
    /// @param value new priority
    void setPriority(int value);

    int getPriority() const;
};

#endif //OOP_COMPONENT_H
