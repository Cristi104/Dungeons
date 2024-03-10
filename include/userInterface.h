#ifndef OOP_USERINTERFACE_H
#define OOP_USERINTERFACE_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Component {
private:
    sf::Sprite sprite;
    int priority;
public:
    Component();
    ~Component() = default;
    sf::Sprite& getSprite();
    virtual void draw(sf::RenderWindow& window);
    void setPriority(int priority_p);
    int getPriority() const;
};

#endif //OOP_USERINTERFACE_H
