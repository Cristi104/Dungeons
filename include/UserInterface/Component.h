#ifndef OOP_COMPONENT_H
#define OOP_COMPONENT_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


class Component {
private:
    sf::RectangleShape sprite;
    int priority;
public:

    /// creates an empty component of priority 1
    Component();

    virtual ~Component() = default;

    sf::RectangleShape& getRectangleShape();

    /// draw the Component
    /// @param window draw target
    virtual void draw(sf::RenderWindow& window);

    /// sets the draw order priority 0 - first, 5 - last
    /// @param value new priority
    void setPriority(int value);

    int getPriority() const;
};

#endif //OOP_COMPONENT_H
