#ifndef OOP_PANEL_H
#define OOP_PANEL_H

#include <vector>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include "../Graphics/GameWindow.h"
#include "Component.h"
#include "Button.h"
#include "Label.h"

class Panel : public EventHandler , public Drawn{
protected:
    bool visible;
    std::vector<Component*> components;

protected:

    void addPos(float x, float y) override;
public:

    Panel();

    virtual ~Panel();

    Panel(const Panel& panel) = delete;

    Panel& operator=(const Panel& panel) = delete;

    bool handleEvent(const sf::Event& event) override;

    /// draws the Panel. Components are drawn in order of the priority attribute from
    /// 0 - first drawn, behind everything else to
    /// 5 - last drawn, on top of everything else
    /// @param window draw target
    void draw(sf::RenderWindow& window) override;

    /// adds a component to the panel
    /// @return index of the component;
    int addComponent(Component* component);

    /// toggles between hidden and visible
    void toggleVisibility();

    Component* getComponent(int index);

    [[nodiscard]] bool isVisible() const;
};

#endif //OOP_PANEL_H
