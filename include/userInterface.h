#ifndef OOP_USERINTERFACE_H
#define OOP_USERINTERFACE_H

#include <vector>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

class Component {
private:
    sf::Sprite sprite;
    int priority;
public:
    Component();
    virtual ~Component() = default;
    sf::Sprite& getSprite();
    virtual void draw(sf::RenderWindow& window);
    void setPriority(int priority_p);
    int getPriority() const;
};

class Label : public Component {
private:
    sf::Text text;
    static sf::Font font;
public:
    static void initFont();
    Label();
    ~Label() override = default;
    void setText(const std::string& text_p, int maxLength_p);
    void draw(sf::RenderWindow& window) override;
};
#endif //OOP_USERINTERFACE_H
