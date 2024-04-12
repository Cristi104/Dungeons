#ifndef OOP_PANEL_H
#define OOP_PANEL_H

#include <vector>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include "../Graphics/window.h"
#include "Component.h"
#include "Button.h"
#include "Label.h"

class Panel {
private:
    std::vector<Component*> components;
    bool isShown;
public:

    Panel();

    ~Panel();

    /// event handler send events to this so that they will be processed
    /// @return true if the event was used in any way
    bool handleEvent(const sf::Event& event);

    /// draws the Panel
    /// @param window draw target
    void draw(sf::RenderWindow& window);

    /// adds a component to the panel
    /// @return index of the component;
    int addComponent(Component* component);

    /// toggles between hidden and shown
    void toggleVisibility();

    Component* getComponent(int index);
};
#endif //OOP_PANEL_H
