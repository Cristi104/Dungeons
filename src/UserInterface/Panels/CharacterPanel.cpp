#include "../../../include/UserInterface/Panels/CharacterPanel.h"
#include "../../../include/UserInterface/Panels/MovePopup.h"
#include "../../../include/UserInterface/Border.h"

CharacterPanel::CharacterPanel(Entity *entity) :Panel(){
    this->entity = entity;
    auto* border = new Border({0,
                               (int)(440 * Settings::getInstance()->getScaleHeight()),
                               Settings::getInstance()->getResolutionWidth() / 2,
                               (int)((720 - 440)* Settings::getInstance()->getScaleHeight())},1,"blueBorder");
    this->addComponent(border);
    auto* healthBarBackground = new Component();
    healthBarBackground->getRectangleShape().setTexture(GameWindow::getTexture("HealthBar"));
    healthBarBackground->getRectangleShape().setSize({380 * Settings::getInstance()->getScaleWidth(),
                                                      32 * Settings::getInstance()->getScaleHeight()});
    healthBarBackground->addPosition<sf::Vector2f>({210 * Settings::getInstance()->getScaleWidth(),
                                                    650 * Settings::getInstance()->getScaleHeight()});
    this->addComponent(healthBarBackground);
    auto* healthBar = new Component();
    healthBar->getRectangleShape().setTexture(GameWindow::getTexture("Health"));
    healthBar->getRectangleShape().setSize({361 * Settings::getInstance()->getScaleWidth(),
                                            32 * Settings::getInstance()->getScaleHeight()});
    healthBar->addPosition<sf::Vector2f>({219.5f * Settings::getInstance()->getScaleWidth(),
                                          650 * Settings::getInstance()->getScaleHeight()});
    healthBar->getRectangleShape().setScale({(float)this->entity->getHealth()/ (float)this->entity->getMaxHealth(),1});
    this->addComponent(healthBar);
    MovePopup* popup = nullptr;
    for(int i = 0; i < 6; i++){
        if(i < 4){
            popup = new MovePopup(&entity->getMoves()[i]);
            popup->getRectangleShape().setTexture(GameWindow::getTexture(entity->getMoves()[i].getName()));
        }
        if(i == 4){
            popup = new MovePopup(new Move);
            popup->getRectangleShape().setTexture(GameWindow::getTexture("Switch"));
        }
        if(i == 5){
            popup = new MovePopup(new Move);
            popup->getRectangleShape().setTexture(GameWindow::getTexture("Skip"));
        }
        if(popup){
            popup->setBoundingBox({0,
                                   0,
                                   64 * Settings::getInstance()->getScaleWidth(),
                                   64 * Settings::getInstance()->getScaleHeight()});
            popup->getRectangleShape().setSize({64 * Settings::getInstance()->getScaleWidth(), 64 * Settings::getInstance()->getScaleHeight()});
            popup->addPosition<sf::Vector2f>({(float)(210 + 65 * i) * Settings::getInstance()->getScaleWidth(), (470 * Settings::getInstance()->getScaleHeight())});
            this->addComponent(popup);
        }
    }
    const Stats& stats = entity->getStats();
    auto* label = new Label("Speed: " + std::to_string(stats.getValue(EffectType::SPEED)),20,20);
    label->getText().setFillColor({100,100,100});
    label->addPosition<sf::Vector2f>({210 * Settings::getInstance()->getScaleWidth(), 570 * Settings::getInstance()->getScaleHeight()});
    this->addComponent(label);
    label = new Label("Stun resist: " + std::to_string(stats.getValue(EffectType::STUN)) + '%',20,20);
    label->getText().setFillColor({100,100,100});
    label->addPosition<sf::Vector2f>({410 * Settings::getInstance()->getScaleWidth(), 570 * Settings::getInstance()->getScaleHeight()});
    this->addComponent(label);
    label = new Label("Bleed resist: " + std::to_string(stats.getValue(EffectType::BLEED)) + '%',20,20);
    label->getText().setFillColor({100,100,100});
    label->addPosition<sf::Vector2f>({210 * Settings::getInstance()->getScaleWidth(), 610 * Settings::getInstance()->getScaleHeight()});
    this->addComponent(label);
    label = new Label("Burn resist: " + std::to_string(stats.getValue(EffectType::BURN)) + '%',20,20);
    label->getText().setFillColor({100,100,100});
    label->addPosition<sf::Vector2f>({410 * Settings::getInstance()->getScaleWidth(), 610 * Settings::getInstance()->getScaleHeight()});
    this->addComponent(label);
    label = new Label(std::to_string(entity->getHealth()) + "/" + std::to_string(entity->getMaxHealth()),20,20);
    label->getText().setFillColor({116,30,43});
    label->addPosition<sf::Vector2f>({370 * Settings::getInstance()->getScaleWidth(), 680 * Settings::getInstance()->getScaleHeight()});
    this->addComponent(label);
    for(int i = 1; i <= 6; i++){
        label = new Label(std::to_string(i),18);
        label->addPosition<sf::Vector2f>({(float)(210-32-8 + 65 * i) * Settings::getInstance()->getScaleWidth(), 530 * Settings::getInstance()->getScaleHeight()});
        this->addComponent(label);
    }
    auto* component = new Component;
    component->getRectangleShape().setTexture(entity->getSprite().getSprite()->getTexture());
    component->getRectangleShape().setSize({120 * Settings::getInstance()->getScaleWidth(),
                                            200 * Settings::getInstance()->getScaleHeight()});
    component->addPosition<sf::Vector2f>({30 * Settings::getInstance()->getScaleWidth(), 470 * Settings::getInstance()->getScaleHeight()});
    this->addComponent(component);
    this->toggleVisibility();
}

void CharacterPanel::update() {
    const Stats& stats = entity->getStats();
    this->getComponent(2)->getRectangleShape().setScale({(float)this->entity->getHealth()/ (float)this->entity->getMaxHealth(),1});
    dynamic_cast<Label*>(this->getComponent(9))->setFormatedText("Speed: " + std::to_string(stats.getValue(EffectType::SPEED)));
    dynamic_cast<Label*>(this->getComponent(10))->setFormatedText("Stun resist: " + std::to_string(stats.getValue(EffectType::STUN)) + '%');
    dynamic_cast<Label*>(this->getComponent(11))->setFormatedText("Bleed resist: " + std::to_string(stats.getValue(EffectType::BLEED))+ '%');
    dynamic_cast<Label*>(this->getComponent(12))->setFormatedText("Burn resist: " + std::to_string(stats.getValue(EffectType::BURN)) + '%');
    dynamic_cast<Label*>(this->getComponent(13))->setFormatedText(std::to_string(this->entity->getHealth()) + "/" + std::to_string(this->entity->getMaxHealth()));
}
