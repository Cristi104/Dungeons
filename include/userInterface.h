#ifndef OOP_USERINTERFACE_H
#define OOP_USERINTERFACE_H

#include <vector>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Mouse.hpp>

class Component {
private:
    sf::RectangleShape sprite;
    int priority;
public:
    Component();
    virtual ~Component() = default;
    sf::RectangleShape& getRectangleShape();
    virtual void draw(sf::RenderWindow& window_p);
    void setPriority(int priority_p);
    int getPriority() const;
};

class Label : public Component {
private:
    sf::Text text;
    static sf::Font font;
    void setText(const std::string& text_p, int maxLength_p);
public:
    static void initFont();
    Label();
    explicit Label(const std::string& text_p, int maxLength_p = 12);
    ~Label() override = default;
    void draw(sf::RenderWindow& window_p) override;
};

class Button : public Component {
private:
    sf::IntRect boundingBox;
    sf::RectangleShape icon;
public:
    Button();
    ~Button() override = default;
    bool isPressed();
    void setBoundingBox(const sf::IntRect& boundingBox_p);
    sf::RectangleShape& getIcon();
    void draw(sf::RenderWindow& window_p) override;
};

class Panel {
private:
    std::vector<Component> components;
    std::vector<Button> buttons;
    bool isShown;
public:
    Panel();
    ~Panel() = default;
    void draw(sf::RenderWindow& window_p);
    void addComponent(const Component& component_p);
    void addButton(const Button& button_p);
    void toggleVisibility();
    Component& getComponent(int index_p);
    Button& getButton(int index_p);
};
#endif //OOP_USERINTERFACE_H
