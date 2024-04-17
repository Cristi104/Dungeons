#ifndef OOP_BORDER_H
#define OOP_BORDER_H

#include <SFML/Graphics/RenderTexture.hpp>
#include "Component.h"

class Border : public Component{
private:
    sf::RenderTexture target;

public:

    /// creates a basic Border of priority 0
    explicit Border(int priority = 0);

    /// creates a Border of priority 0 with a specif texture
    /// @param rect bounding box of the border
    /// @param scale border texture scaling
    /// @param name name of border texture (without corner just the side)
    explicit Border(sf::IntRect rect, int scale = 1, const std::string& name = "border", int priority = 0);

    ~Border() override = default;
};


#endif //OOP_BORDER_H
