#ifndef OOP_DRAWN_H
#define OOP_DRAWN_H

#include <SFML/Graphics/RenderWindow.hpp>

class Drawn{
protected:

    virtual void addPos(float x, float y) = 0;
public:

    /// draw the object to the screen
    /// @param window draw target
    virtual void draw(sf::RenderWindow& window) = 0;

    /// adds the position vector to all components included in the object
    /// @tparam T a type of vector with x and y coordinates
    /// @param position vector to be added
    template<typename T>
    void addPosition(T position) {
        this->addPos(position.x, position.y);
    }
};


#endif //OOP_DRAWN_H
