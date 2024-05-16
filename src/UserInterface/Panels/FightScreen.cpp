#include <iostream>
#include <valarray>
#include <thread>
#include "../../../include/UserInterface/Panels/FightScreen.h"
#include "../../../include/UserInterface/Border.h"
#include "../../../include/UserInterface/Panels/MapPanel.h"

FightScreen* FightScreen::singleton = nullptr;

FightScreen::FightScreen() :Panel() {
    this->selectedEntity = 3;
    this->font.loadFromFile("../res/fonts/8bitOperatorPlus8-Regular.ttf");
    this->selectedMove = 0;
    this->entities = new Entity*[8];
    for(int i = 0; i < 8; i++)
        this->entities[i] = nullptr;
    for(int i = 0; i < 8; i++){
        auto* button = new Button;
        sf::Vector2f position = FightScreen::getCoordsOfIndex(i);
        button->setBoundingBox({position.x,
                                position.y,
                                120 * Settings::getInstance()->getScaleWidth(),
                                200 * Settings::getInstance()->getScaleHeight()});
        this->addComponent(button);
    }
    for(int i = 0; i < 8; i++){
        auto* component = new Component(2);
        if(i < 4)
            component->getRectangleShape().setTexture(GameWindow::getTexture("SelectorAlly"));
        else
            component->getRectangleShape().setTexture(GameWindow::getTexture("SelectorEnemy"));
        component->getRectangleShape().setSize({80 * Settings::getInstance()->getScaleWidth(),
                                                28 * Settings::getInstance()->getScaleHeight()});
        component->addPosition<sf::Vector2f>(FightScreen::getCoordsOfIndex(i));
        component->addPosition<sf::Vector2f>({10 * Settings::getInstance()->getScaleWidth(),
                                              185 * Settings::getInstance()->getScaleHeight()});
        this->addComponent(component);
    }
    for(int i = 0; i < 8; i++){
        auto* component = new Component();
        component->getRectangleShape().setTexture(GameWindow::getTexture("HealthBar"));
        component->getRectangleShape().setSize({80 * Settings::getInstance()->getScaleWidth(),
                                                12 * Settings::getInstance()->getScaleHeight()});
        component->addPosition<sf::Vector2f>(FightScreen::getCoordsOfIndex(i));
        component->addPosition<sf::Vector2f>({10 * Settings::getInstance()->getScaleWidth(),
                                              205 * Settings::getInstance()->getScaleHeight()});
        this->addComponent(component);
    }
    for(int i = 0; i < 8; i++){
        auto* component = new Component();
        component->getRectangleShape().setTexture(GameWindow::getTexture("Health"));
        component->getRectangleShape().setSize({76 * Settings::getInstance()->getScaleWidth(),
                                                12 * Settings::getInstance()->getScaleHeight()});
        component->addPosition<sf::Vector2f>(FightScreen::getCoordsOfIndex(i));
        component->addPosition<sf::Vector2f>({12 * Settings::getInstance()->getScaleWidth(),
                                              205 * Settings::getInstance()->getScaleHeight()});
        this->addComponent(component);
    }
    this->characterPanel = new CharacterPanel*[4];
    for(int i = 0; i < 4; i++)this->characterPanel[i] = nullptr;
    this->currentMap = new Map;
    this->mapPanel = new MapPanel(this->currentMap);
    this->mapPanel->toggleVisibility();
    this->toggleVisibility();
}

FightScreen::~FightScreen() {
    for(int i = 0; i < 8; i++)
        if(this->entities[i] != nullptr)
            delete this->entities[i];
    delete[] this->entities;
    for(int i = 0; i < 4; i++)
        if(this->characterPanel[i] != nullptr)
            delete this->characterPanel[i];
    delete this->characterPanel;
    delete this->mapPanel;
    delete this->currentMap;
}

int FightScreen::getIndex(Positions position) {
    int x = static_cast<int>(position);
    int i;
    for(i = 0; x != 1; i++)x /= 2;
    return i;
}

sf::Vector2f FightScreen::getCoordsOfIndex(int index) {
    sf::Vector2f position;
    position.y = 200 * Settings::getInstance()->getScaleHeight();
    if(index < 4){
        position.x = (float)(50 + 130 * index) * Settings::getInstance()->getScaleWidth();
    } else {
        position.x = (float)(130 + 130 * index) * Settings::getInstance()->getScaleWidth();
    }
    return position;
}

void FightScreen::addEntity(Entity* entity) {
    int index = entity->getPosition();
    this->entities[index] = entity;
    if(index < 4)
        this->characterPanel[index] = new CharacterPanel(entity);
    entity->getSprite().getSprite()->setPosition(FightScreen::getCoordsOfIndex(index));
}

void FightScreen::swapEntities(int index1, int index2) {
    Entity* p = this->entities[index1];
    this->entities[index1] = this->entities[index2];
    this->entities[index2] = p;
    if(index1 < 4 && index2 < 4){
        auto* aux = this->characterPanel[index2];
        this->characterPanel[index2] = this->characterPanel[index1];
        this->characterPanel[index1] = aux;
    }
    if(this->entities[index1])
        this->entities[index1]->getSprite().getSprite()->setPosition(FightScreen::getCoordsOfIndex(index1));
    if(this->entities[index2])
        this->entities[index2]->getSprite().getSprite()->setPosition(FightScreen::getCoordsOfIndex(index2));
}

void FightScreen::deleteEntity(int index) {
    delete this->entities[index];
    this->entities[index] = nullptr;
    if(index < 4){
        for(int j = 0; j < index - 1; j++)
            this->swapEntities(j,j + 1);
        delete this->characterPanel[index];
        this->characterPanel[index] = nullptr;
    } else {
        for(int j = 7; j > index + 1; j--)
            this->swapEntities(j,j - 1);
    }
}

void FightScreen::draw(sf::RenderWindow &window) {
    for(int i = 0; i < 8; i++)
        if(entities[i] != nullptr){
//            entities[i]->getSprite().getSprite().setPosition(FightScreen::getCoordsOfIndex(i));
//            window.draw(entities[i]->getSprite());
            this->entities[i]->getSprite().draw(window);
        }
    for(int i = 0; i < 8; i++){
        if(this->selectedMove >= 1 && this->selectedMove <= 4)
            if((int)this->entities[turnOrder.top()]->getMoves()[this->selectedMove-1].getRange() & (int)FightScreen::getPosition(i) &&
                    this->entities[i] != nullptr)
                this->getComponent(i + 8)->draw(window);
    }
    for(int i = 0; i < 8; i++){
        if(this->entities[i]){
            this->getComponent(i+16)->draw(window);
            this->getComponent(i+24)->getRectangleShape().setScale({(float)this->entities[i]->getHealth()/ (float)this->entities[i]->getMaxHealth(),1});
            this->getComponent(i+24)->draw(window);
        }
    }
    for(int i =0; i < (int)this->animations.size(); i++){
        this->animations[i]->draw(window);
        if(static_cast<Animation<sf::Text>*>(this->animations[i])->isDone()){
            delete this->animations[i];
            this->animations.erase(this->animations.begin() + i);
            i--;
        }
    }
    this->mapPanel->draw(window);
    if(this->characterPanel[this->selectedEntity])
        this->characterPanel[this->selectedEntity]->draw(window);
}

FightScreen *FightScreen::getInstance() {
    if(FightScreen::singleton == nullptr)
        FightScreen::singleton = new FightScreen;
    return FightScreen::singleton;
}

int FightScreen::handleEvent(const sf::Event &event) {
    if(this->characterPanel[this->selectedEntity])
        if(this->characterPanel[this->selectedEntity]->handleEvent(event))
            return true;
//    if(this->mapPanel->handleEvent(event))
//        return true;
    if(!this->visible)
        return 0;
    if(turnOrder.top() >= 4)
        return 0;
    if(event.type == sf::Event::KeyPressed){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) &&
           (FightScreen::getPosition(turnOrder.top()) &
            this->entities[turnOrder.top()]->getMoves()[0].getCastPosition())){
            this->selectedMove = 1;
            return 1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) &&
           (FightScreen::getPosition(turnOrder.top()) &
            this->entities[turnOrder.top()]->getMoves()[1].getCastPosition())){
            this->selectedMove = 2;
            return 2;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) &&
           (FightScreen::getPosition(turnOrder.top()) &
            this->entities[turnOrder.top()]->getMoves()[2].getCastPosition())){
            this->selectedMove = 3;
            return 3;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) &&
           (FightScreen::getPosition(turnOrder.top()) &
            this->entities[turnOrder.top()]->getMoves()[3].getCastPosition())){
            this->selectedMove = 4;
            return 4;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)){
            this->selectedMove = 5;
            return 5;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)){
            std::cout << "end turn\n";
            this->endEntityTurn();
            return 6;
        }
    }
    if(event.type == sf::Event::MouseButtonPressed){
        if(this->selectedMove == 0)
            return 0;
        Move* move;
        if(this->selectedMove < 5){
            move = &this->entities[this->turnOrder.top()]->getMoves()[this->selectedMove - 1];
            for (int i = 0; i < 8; i++) {
                auto* handler = dynamic_cast<Button *>(this->components[i]);
                if(!handler)
                    continue;
                if (!handler->handleEvent(event))
                    continue;
                if (!(move->getRange() & getPosition(i)))
                    continue;
                if(move->isAoe()){
                    for(int j = 0; j < 8; j++){
                        if(FightScreen::getPosition(j) & move->getRange())
                            this->hit(move,j);
                    }
                } else
                    this->hit(move, i);
                this->endEntityTurn();
                return true;
            }
        } else {
            for(int i = 0; i < 4; i++){
                if(i == turnOrder.top())
                    continue;
                try{
                    if(!dynamic_cast<Button*>(this->components[i])->handleEvent(event))
                        continue;
                    this->swapEntities(i, this->turnOrder.top());
                    return true;
                }catch(std::bad_cast&){}
            }
        }
    }
    return 0;
}

void FightScreen::turn() {
    if(this->turnOrder.empty()){
        std::cout << "new turn\n";
        for(int i = 0; this->turnOrder.size() != 8; i++){
            for(int j = 0; j < 8; j++){
                if(this->entities[j] == nullptr)
                    continue;
                if(this->entities[j]->getStats().getValue(EffectType::SPEED) == i){
                    this->turnOrder.push(j);
                }
            }
            if(i > 40)
                break;
        }
    }
}

void FightScreen::endEntityTurn() {
    this->entities[turnOrder.top()]->getSprite().reset();
    this->turnOrder.pop();
    this->selectedMove = 0;
    this->turn();
    this->entities[turnOrder.top()]->turn();
    if(this->turnOrder.top() < 4){
        this->characterPanel[turnOrder.top()]->update();
    }
//    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

Positions FightScreen::getPosition(int index) {
    return static_cast<Positions>(pow(2,index));
}

void FightScreen::hit(Move *move, int index) {
    int ret = this->entities[index]->getHit(*move);
    Animation<sf::Text>* animation;
    std::vector<sf::Vector2f> moves = {{0,-42 * Settings::getInstance()->getScaleHeight()},
                                       {0,-34 * Settings::getInstance()->getScaleHeight()},
                                       {0,-26 * Settings::getInstance()->getScaleHeight()},
                                       {0,-20 * Settings::getInstance()->getScaleHeight()},
                                       {0,-15 * Settings::getInstance()->getScaleHeight()},
                                       {0,-13 * Settings::getInstance()->getScaleHeight()},
                                       {0,-8 * Settings::getInstance()->getScaleHeight()},
                                       {0,-3 * Settings::getInstance()->getScaleHeight()},};
    if(ret != -1){
        std::cout << "ok";
        animation = new Animation<sf::Text>(0,8,5);
        animation->setMoves(moves);
        animation->getSprite()->setString(std::to_string(-move->getDamage()));
        animation->getSprite()->setCharacterSize(42);
        animation->getSprite()->setPosition(FightScreen::getCoordsOfIndex(index)+ sf::Vector2f(30 * Settings::getInstance()->getScaleWidth(),
                                                                                               80 * Settings::getInstance()->getScaleWidth()));
        animation->getSprite()->setFont(this->font);
        if(move->getDamage() > 0)
            animation->getSprite()->setFillColor({200,45,34});
        else
            animation->getSprite()->setFillColor({20,195,34});
        this->animations.push_back(animation);
        if(ret > 0){
            std::cout << "okk";
            animation = new Animation<sf::Text>(0,8,5);
            switch (move->getStatusEffect().getType()) {
                case EffectType::SPEED:
                    animation->getSprite()->setString("Debuf");
                    break;
                case EffectType::STUN:
                    animation->getSprite()->setString("Stun");
                    break;
                case EffectType::BLEED:
                    animation->getSprite()->setString("Bleed");
                    break;
                case EffectType::BURN:
                    animation->getSprite()->setString("Burn");
                    break;
                default:
                    break;
            }
            animation->setMoves(moves);
            animation->getSprite()->setCharacterSize(42);
            animation->getSprite()->setPosition(FightScreen::getCoordsOfIndex(index)+ sf::Vector2f(20 * Settings::getInstance()->getScaleWidth(),
                                                                                                   110 * Settings::getInstance()->getScaleWidth()));
            animation->getSprite()->setFont(this->font);
            this->animations.push_back(animation);
        } else{
            animation = new Animation<sf::Text>(0,8,5);
            animation->setMoves(moves);
            animation->getSprite()->setString("Miss");
            animation->getSprite()->setCharacterSize(42);
            animation->getSprite()->setPosition(FightScreen::getCoordsOfIndex(index)+ sf::Vector2f(30 * Settings::getInstance()->getScaleWidth(),
                                                                                                   80 * Settings::getInstance()->getScaleWidth()));
            animation->getSprite()->setFont(this->font);
        }

    }
}
