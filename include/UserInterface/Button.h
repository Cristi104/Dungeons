#ifndef OOP_BUTTON_H
#define OOP_BUTTON_H

#include "Component.h"
#include "SFML/Window/Event.hpp"
#include "EventHandler.h"

class Button : public Component , public EventHandler<bool>{
private:
    bool wasPressed;

protected:
    sf::FloatRect boundingBox;

    void addPos(float x, float y) override;
public:

    /// creates a 50x50 button with priority 5
    explicit Button(int priority = 5);

    ~Button() override = default;

    bool handleEvent(const sf::Event& event) override;

    /// @return true for every frame in which the button was pressed
    bool isPressed();

    /// sets the size and position of the click hitBox
    void setBoundingBox(const sf::FloatRect& box);

    virtual /// draws the Button
    /// @param window draw target
    void draw(sf::RenderWindow& window) override;
};


#endif //OOP_BUTTON_H
