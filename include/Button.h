#ifndef OOP_BUTTON_H
#define OOP_BUTTON_H

#include "Component.h"

class Button : public Component {
private:
    sf::IntRect boundingBox;
    sf::RectangleShape icon;
    bool wasPressed;
public:
    Button();
    ~Button() override = default;
    bool isPressed();
    void setBoundingBox(const sf::IntRect& box);
    sf::RectangleShape& getIcon();
    void draw(sf::RenderWindow& window) override;
};


#endif //OOP_BUTTON_H
