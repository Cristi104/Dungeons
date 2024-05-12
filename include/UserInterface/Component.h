#ifndef OOP_COMPONENT_H
#define OOP_COMPONENT_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Graphics/Drawn.h"
#include "../Graphics/Drawn.h"

class Component : public Drawn{
private:
    sf::RectangleShape sprite;
    int priority;
protected:

    void addPos(float x, float y) override;
public:

    /// creates an empty component of priority 1
    explicit Component(int priority = 1);

    virtual ~Component() = default;

    sf::RectangleShape& getRectangleShape();

    void draw(sf::RenderWindow& window) override;

    /// sets the draw order priority 0 - first, 5 - last
    /// @param value new priority
    void setPriority(int value);

    int getPriority() const;
};

#endif //OOP_COMPONENT_H
