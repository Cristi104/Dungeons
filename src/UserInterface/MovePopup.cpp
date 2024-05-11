#include "../../include/UserInterface/MovePopup.h"
#include "../../include/UserInterface/Border.h"
#include <cmath>

MovePopup::MovePopup(const Move *move) : PopupPanel(){
    this->move = move;
    auto* border = new Border({(int)(64 * Settings::getInstance()->getScaleWidth()), 0,
                                 (int)(150 * Settings::getInstance()->getScaleWidth()),
                                 (int)(150 * Settings::getInstance()->getScaleHeight())},
                                1, "blueBorder");
    this->addComponent(border);
    auto* component = new Component;
    component->getRectangleShape().setTexture(GameWindow::getTexture("Positions"));
    component->getRectangleShape().setSize({(120 * Settings::getInstance()->getScaleWidth()),
                                            (24 * Settings::getInstance()->getScaleHeight())});
    component->addPosition<sf::Vector2f>({(64 + 16) * Settings::getInstance()->getScaleWidth(), 8  * Settings::getInstance()->getScaleHeight()});
    this->addComponent(component);
    if(move->isAoe()){
        if(move->getRange() >= 16){
            component = new Component;
            component->getRectangleShape().setTexture(GameWindow::getTexture("EnemyPosAoe"));
            component->setPriority(2);
            component->getRectangleShape().setSize({(60 * Settings::getInstance()->getScaleWidth()),
                                                    (24 * Settings::getInstance()->getScaleHeight())});
            component->addPosition<sf::Vector2f>({(64 + 16 + 60) * Settings::getInstance()->getScaleWidth(), 8  * Settings::getInstance()->getScaleHeight()});
            this->addComponent(component);
        } else {
            component = new Component;
            component->getRectangleShape().setTexture(GameWindow::getTexture("AllyPosAoe"));
            component->setPriority(2);
            component->getRectangleShape().setSize({(60 * Settings::getInstance()->getScaleWidth()),
                                                    (24 * Settings::getInstance()->getScaleHeight())});
            component->addPosition<sf::Vector2f>({(64 + 16) * Settings::getInstance()->getScaleWidth(), 8  * Settings::getInstance()->getScaleHeight()});
            this->addComponent(component);
        }
    } else {
        auto sum = static_cast<Positions>(move->getRange() | move->getCastPosition());
//        auto sum = static_cast<Positions>(256-1);
        for(int i = 0; i < 8; i++){
            if(sum & (int)pow(2,i)) {
                if ((int) pow(2, i) <= 8) {
                    component = new Component;
                    component->getRectangleShape().setTexture(GameWindow::getTexture("AllyPos"));
                    component->addPosition<sf::Vector2f>({(float) (64 + 16 + 6 + 13.5 * i) * Settings::getInstance()->getScaleWidth(),
                                            (float) (15.5 * Settings::getInstance()->getScaleHeight())});
                    component->getRectangleShape().setSize({9 * Settings::getInstance()->getScaleWidth(),
                                                            9 * Settings::getInstance()->getScaleHeight()});
                    component->setPriority(2);
                    this->addComponent(component);
                } else {
                    component = new Component;
                    component->getRectangleShape().setTexture(GameWindow::getTexture("EnemyPos"));
                    component->addPosition<sf::Vector2f>(
                            {(float) (64 + 16 + 10.5 + 13.5 * i) * Settings::getInstance()->getScaleWidth(),
                             (float) (15.5 * Settings::getInstance()->getScaleHeight())});
                    component->getRectangleShape().setSize({9 * Settings::getInstance()->getScaleWidth(),
                                                            9 * Settings::getInstance()->getScaleHeight()});
                    component->setPriority(2);
                    this->addComponent(component);
                }
            }
        }
    }
    auto* label = new Label(move->getName(),14,18);
    label->addPosition<sf::Vector2f>({(64 + 16) * Settings::getInstance()->getScaleWidth(),16 * 2 * Settings::getInstance()->getScaleHeight()});
    this->addComponent(label);
    if(move->getAccuracy() < 200){
        label = new Label("Acc: " + std::to_string(move->getAccuracy()) + "%");
        label->addPosition<sf::Vector2f>({(64 + 16) * Settings::getInstance()->getScaleWidth(),16 * 3 * Settings::getInstance()->getScaleHeight()});
        this->addComponent(label);
    }
    if(move->getDamage() > 0){
        label = new Label("Dmg: " + std::to_string(move->getDamage()));
        label->addPosition<sf::Vector2f>({(64 + 16) * Settings::getInstance()->getScaleWidth(),16 * 4 * Settings::getInstance()->getScaleHeight()});
        this->addComponent(label);
    }
    if(move->getDamage() < 0){
        label = new Label("Heal: " + std::to_string(-move->getDamage()));
        label->addPosition<sf::Vector2f>({(64 + 16) * Settings::getInstance()->getScaleWidth(),16 * 4 * Settings::getInstance()->getScaleHeight()});
        this->addComponent(label);
    }
    const StatusEffect& statusEffect = move->getStatusEffect();
    if(statusEffect.getType()){
        label = new Label();
        std::string name;
        switch (statusEffect.getType()) {
            case 1:
                name = "Speed";
                break;
            case 2:
                name = "Accuracy";
                break;
            case 4:
                name = "Stun";
                break;
            case 8:
                name = "Bleed";
                break;
            case 16:
                name = "Burn";
                break;
            default:
                name = "None";
        }
        label->setFormatedText("On hit: " + name +"\n " + std::to_string(statusEffect.getValue()) + " (" + std::to_string(statusEffect.getDuration()) + " turns)\n Chance:" + std::to_string(statusEffect.getChance()) + "%");
        label->addPosition<sf::Vector2f>({(64 + 16) * Settings::getInstance()->getScaleWidth(), 16 * 5 * Settings::getInstance()->getScaleHeight()});
        this->addComponent(label);
    }
}
