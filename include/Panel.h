#ifndef OOP_PANEL_H
#define OOP_PANEL_H

#include <vector>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Mouse.hpp>
#include "Component.h"
#include "Button.h"
#include "Label.h"

class Panel {
private:
    std::vector<Component> components;
    std::vector<Button> buttons;
    std::vector<Label> labels;
    bool isShown;
public:
    Panel();
    ~Panel() = default;
    void draw(sf::RenderWindow& window);
    void addComponent(const Component& component);
    void addButton(const Button& button);
    void addLabel(const Label& label);
    void toggleVisibility();
    Component& getComponent(int index);
    Button& getButton(int index);
    Label& getLabel(int index);
};
#endif //OOP_PANEL_H
