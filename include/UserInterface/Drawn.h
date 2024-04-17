#ifndef OOP_DRAWN_H
#define OOP_DRAWN_H

#include <SFML/Graphics/RenderWindow.hpp>

class Drawn{
public:

    /// draw the object to the screen
    /// @param window draw target
    virtual void draw(sf::RenderWindow& window) = 0;

    /// adds the position vector to all components included in the object
    /// @param position vector to be added
    virtual void addPosition(sf::Vector2f position) = 0;
};

#endif //OOP_DRAWN_H
