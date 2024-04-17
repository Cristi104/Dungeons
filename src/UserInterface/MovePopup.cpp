#include "../../include/UserInterface/MovePopup.h"
#include "../../include/UserInterface/Border.h"

MovePopup::MovePopup(const Move *move) : PopupPanel(){
    this->move = move;
    auto* border = new Border({48, 0,
                                 (int)(150 * Settings::getInstance()->getScaleWidth()),
                                 (int)(200 * Settings::getInstance()->getScaleHeight())},
                                1, "blueBorder");
    this->addComponent(border);
    auto* component = new Component;
    component->getRectangleShape().setTexture(GameWindow::getTexture("Positions"));
    component->getRectangleShape().setSize({(120 * Settings::getInstance()->getScaleWidth()),
                                            (24 * Settings::getInstance()->getScaleHeight())});
    component->addPosition({48 + 16, 8});
    this->addComponent(component);
    auto* label = new Label(move->getName());
    label->addPosition({48 + 16,16 * 2});
    this->addComponent(label);
    label = new Label("Acc: " + std::to_string(move->getAccuracy()) + "%");
    label->addPosition({48 + 16,16 * 3});
    this->addComponent(label);
    if(move->getDamage() > 0){
        label = new Label("Dmg: " + std::to_string(move->getDamage()) + "%");
        label->addPosition({48 + 16,16 * 4});
        this->addComponent(label);
    }
    if(move->getDamage() < 0){
        label = new Label("Heal: " + std::to_string(-move->getDamage()) + "%");
        label->addPosition({48 + 16,16 * 4});
        this->addComponent(label);
    }
    StatusEffect const& statusEffect = move->getStatusEffect();
//    if(statusEffect.getType()){
        label = new Label();
        label->setFormatedText("On hit:\n " + std::to_string(statusEffect.getType()) +" (" +std::to_string(statusEffect.getDuration()) + ")\n");
        label->addPosition({48 + 16, 16 * 5});
        this->addComponent(label);
//    }
}
