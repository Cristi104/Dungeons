#ifndef OOP_BUTTON_H
#define OOP_BUTTON_H

#include "Component.h"
#include "SFML/Window/Event.hpp"

class Button : public Component {
private:
    sf::IntRect boundingBox;
    sf::RectangleShape icon;
    bool wasPressed;
public:

    /// creates a 50x50 button with priority 5
    Button();

    ~Button() override = default;

    /// event handler send events to this so that they will be processed
    /// @return true if the event was used in any way
    bool handleEvent(const sf::Event& event);

    /// @return true for every frame in which the button was pressed
    bool isPressed();

    /// sets the size and position of the click hitBox
    void setBoundingBox(const sf::IntRect& box);

    sf::RectangleShape& getIcon();

    /// draws the Button
    /// @param window draw target
    void draw(sf::RenderWindow& window) override;
};


#endif //OOP_BUTTON_H
