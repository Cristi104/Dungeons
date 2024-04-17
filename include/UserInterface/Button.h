#ifndef OOP_BUTTON_H
#define OOP_BUTTON_H

#include "Component.h"
#include "SFML/Window/Event.hpp"
#include "EventHandler.h"

class Button : public Component , public EventHandler{
private:
    sf::RectangleShape icon;
    bool wasPressed;

protected:
    sf::IntRect boundingBox;

public:

    /// creates a 50x50 button with priority 5
    explicit Button(int priority = 5);

    ~Button() override = default;

    bool handleEvent(const sf::Event& event) override;

    /// @return true for every frame in which the button was pressed
    bool isPressed();

    /// sets the size and position of the click hitBox
    void setBoundingBox(const sf::IntRect& box);

    sf::RectangleShape& getIcon();

    /// draws the Button
    /// @param window draw target
    void draw(sf::RenderWindow& window) override;

    void addPosition(sf::Vector2f position) override;
};


#endif //OOP_BUTTON_H
