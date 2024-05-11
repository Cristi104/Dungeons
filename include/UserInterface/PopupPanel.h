#ifndef OOP_POPUPPANEL_H
#define OOP_POPUPPANEL_H

#include "Panel.h"

class PopupPanel : public Button{
protected:
    Panel panel;

    void addPos(float x, float y) override;
public:

    PopupPanel();

    ~PopupPanel() override = default;

    /// draws the Button and Panel. Components are drawn in order of the priority attribute from
    /// 0 - first drawn, behind everything else to
    /// 5 - last drawn, on top of everything else
    /// @param window draw target
    void draw(sf::RenderWindow& window) override;

    bool handleEvent(const sf::Event& event) override;

    /// adds a component to the panel
    /// @return index of the component;
    int addComponent(Component* component);
};

#endif //OOP_POPUPPANEL_H
