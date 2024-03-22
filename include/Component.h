#ifndef OOP_COMPONENT_H
#define OOP_COMPONENT_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


class Component {
private:
    sf::RectangleShape sprite;
    int priority;
public:
    Component();
    virtual ~Component() = default;
    sf::RectangleShape& getRectangleShape();
    virtual void draw(sf::RenderWindow& window);
    void setPriority(int value);
    int getPriority() const;
};

#endif //OOP_COMPONENT_H
