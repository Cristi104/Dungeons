#include "../../../include/UserInterface/Panels/MapPanel.h"
#include "../../../include/UserInterface/Border.h"

MapPanel::MapPanel(Map* map) : Panel(){
    this->map = map;
    this->size = map->getSize();
    auto* pComponent = new Component;
    auto* border = new Border({Settings::getInstance()->getResolutionWidth() / 2,
                         (int)(440 * Settings::getInstance()->getScaleHeight()),
                         Settings::getInstance()->getResolutionWidth() / 2,
                         (int)((720 - 440)* Settings::getInstance()->getScaleHeight())},1,"blueBorder");
    this->addComponent(border);
    pComponent->getRectangleShape().setTexture(&this->map->getTexture().getTexture());
    pComponent->getRectangleShape().setSize({(float)(this->size.x * 48) * Settings::getInstance()->getScaleWidth(),
                                             (float)(this->size.y * 48) * Settings::getInstance()->getScaleHeight()});
    pComponent->getRectangleShape().setPosition(((float) Settings::getInstance()->getResolutionWidth()) / 2
                                                    + ((float)Settings::getInstance()->getResolutionWidth() / 2 - pComponent->getRectangleShape().getSize().x) / 2,
                                                ((440) * Settings::getInstance()->getScaleHeight()
                                                    + (280 * Settings::getInstance()->getScaleHeight()- pComponent->getRectangleShape().getSize().y) / 2));
    pComponent->setPriority(0);
    this->addComponent(pComponent);
    this->CurrentPosition = this->size / 2;
    this->Pointer.setTexture(GameWindow::getTexture("AllyPos"));
    this->Pointer.setSize({12 * Settings::getInstance()->getScaleWidth(), 12 * Settings::getInstance()->getScaleHeight()});
    this->Pointer.setPosition(((float) Settings::getInstance()->getResolutionWidth()) / 4 * 3 - 6 * Settings::getInstance()->getScaleWidth(),
                              ((440 - 6 + 140) * Settings::getInstance()->getScaleHeight()));
    if(this->size.x % 2 == 0)
        this->Pointer.setPosition(this->Pointer.getPosition() + sf::Vector2f(24 * Settings::getInstance()->getScaleWidth(),0));
    if(this->size.y % 2 == 0)
        this->Pointer.setPosition(this->Pointer.getPosition() + sf::Vector2f(0, 24 * Settings::getInstance()->getScaleHeight()));
    auto* component = new Button;
    component->setBoundingBox({0, 0,48 * Settings::getInstance()->getScaleWidth(),
                               48 * Settings::getInstance()->getScaleHeight()});
    this->addComponent(component);
}

void MapPanel::draw(sf::RenderWindow &window) {
    Panel::draw(window);
    window.draw(this->Pointer);
}
