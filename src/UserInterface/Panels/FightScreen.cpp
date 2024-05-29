#include <iostream>
#include <valarray>
#include <thread>
#include "../../../include/UserInterface/Panels/FightScreen.h"
#include "../../../include/UserInterface/Border.h"
#include "../../../include/UserInterface/Panels/MapPanel.h"
#include "../../../include/Entity/EnemyAI.h"

FightScreen* FightScreen::singleton = nullptr;

FightScreen::FightScreen() :Panel() {
    this->hasEnded = false;
    this->selectedEntity = 3;
    this->delay = 60;
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
                                180 * Settings::getInstance()->getScaleHeight()});
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
                                              165 * Settings::getInstance()->getScaleHeight()});
        this->addComponent(component);
    }
    for(int i = 0; i < 8; i++){
        auto* component = new Component();
        component->getRectangleShape().setTexture(GameWindow::getTexture("HealthBar"));
        component->getRectangleShape().setSize({80 * Settings::getInstance()->getScaleWidth(),
                                                12 * Settings::getInstance()->getScaleHeight()});
        component->addPosition<sf::Vector2f>(FightScreen::getCoordsOfIndex(i));
        component->addPosition<sf::Vector2f>({10 * Settings::getInstance()->getScaleWidth(),
                                              185 * Settings::getInstance()->getScaleHeight()});
        this->addComponent(component);
    }
    for(int i = 0; i < 8; i++){
        auto* component = new Component();
        component->getRectangleShape().setTexture(GameWindow::getTexture("Health"));
        component->getRectangleShape().setSize({76 * Settings::getInstance()->getScaleWidth(),
                                                12 * Settings::getInstance()->getScaleHeight()});
        component->addPosition<sf::Vector2f>(FightScreen::getCoordsOfIndex(i));
        component->addPosition<sf::Vector2f>({12 * Settings::getInstance()->getScaleWidth(),
                                              185 * Settings::getInstance()->getScaleHeight()});
        this->addComponent(component);
    }
    auto* component = new Component();
    component->getRectangleShape().setSize({1280 * Settings::getInstance()->getScaleWidth(), 440 * Settings::getInstance()->getScaleHeight()});
    component->getRectangleShape().setTexture(GameWindow::getTexture("BackGround"));
    this->addComponent(component);
    for(int i = 0; i < 8; i++){
        component = new Component();
        component->getRectangleShape().setTexture(GameWindow::getTexture("Stunned"));
        component->getRectangleShape().setSize({96 * Settings::getInstance()->getScaleWidth(),
                                                96 * Settings::getInstance()->getScaleHeight()});
        component->addPosition<sf::Vector2f>(FightScreen::getCoordsOfIndex(i));
        component->addPosition<sf::Vector2f>({10 * Settings::getInstance()->getScaleWidth(),
                                              -30 * Settings::getInstance()->getScaleHeight()});
        this->addComponent(component);
    }
    this->characterPanel = new CharacterPanel;
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
    delete this->characterPanel;
    delete this->mapPanel;
    delete this->currentMap;
}

sf::Vector2f FightScreen::getCoordsOfIndex(int index) {
    sf::Vector2f position;
    position.y = 220 * Settings::getInstance()->getScaleHeight();
    if(index < 4){
        position.x = (float)(50 + 130 * index) * Settings::getInstance()->getScaleWidth();
    } else {
        position.x = (float)(195 + 130 * index) * Settings::getInstance()->getScaleWidth();
    }
    return position;
}

void FightScreen::addEntity(Entity* entity) {
    int index = entity->getPosition();
    this->entities[index] = entity;
//    for(int i = 0; i < 4; i++)std::cout<< (int64_t)this->characterPanel[i] <<' ';
//    std::cout << '\n';
//    if(index < 4)
//        this->characterPanel[index] = new CharacterPanel(entity);
    entity->getSprite().getSprite()->setPosition(FightScreen::getCoordsOfIndex(index));
}

void FightScreen::swapEntities(int index1, int index2) {
    Entity* p = this->entities[index1];
    this->entities[index1] = this->entities[index2];
    this->entities[index2] = p;
    std::stack<int> mem;
    int a = 0;
    int b = 0;
    if(!this->turnOrder.empty()){
        for(int i = 1; i <= (int)this->turnOrder.size(); i++){
            if(this->turnOrder.top() == index1){
                a = i;
            } else if(this->turnOrder.top() == index1){
                b = i;
            } else {
                mem.push(turnOrder.top());
            }
            turnOrder.pop();
        }
        int n = (int)mem.size();
        if(a)n++;
        if(b)n++;
        for(int i = 1; i <=n; i++){
            if(i == a){
                turnOrder.push(index2);
            } else if(i == b){
                turnOrder.push(index1);
            } else {
                turnOrder.push(mem.top());
                mem.pop();
            }
        }
    }
//    if(index1 < 4 && index2 < 4){
//        auto* aux = this->characterPanel[index2];
//        this->characterPanel[index2] = this->characterPanel[index1];
//        this->characterPanel[index1] = aux;
//    }
    if(this->entities[index1]){
        this->entities[index1]->getSprite().getSprite()->setPosition(FightScreen::getCoordsOfIndex(index1));
        this->entities[index1]->setPosition(index1);
    }
    if(this->entities[index2]){
        this->entities[index2]->getSprite().getSprite()->setPosition(FightScreen::getCoordsOfIndex(index2));
        this->entities[index2]->setPosition(index2);
    }
}

void FightScreen::deleteEntity(int index) {
    delete this->entities[index];
    this->entities[index] = nullptr;
    if(index < 4){
//        delete this->characterPanel[index];
//        this->characterPanel[index] = nullptr;
//        for(int i = 0; i < 4; i++)std::cout<< (int64_t)this->characterPanel[i] <<' ';
//        std::cout << '\n';
        for(int j = index; j > 0; j--)
            this->swapEntities(j,j - 1);
    } else {
        for(int j = index; j < 7; j++)
            this->swapEntities(j,j + 1);
    }

}

void FightScreen::draw(sf::RenderWindow &window) {
    this->delay--;
    this->getComponent(32)->draw(window);
    for(int i = 0; i < 8; i++)
        if(entities[i] != nullptr){
//            entities[i]->getSprite().getSprite().setPosition(FightScreen::getCoordsOfIndex(i));
//            window.draw(entities[i]->getSprite());
            this->entities[i]->getSprite().draw(window);
        }
    for(int i = 0; i < 8; i++){
        if(this->selectedMove >= 1 && this->selectedMove <= 4)
            if(this->entities[turnOrder.top()]->getMoves()[this->selectedMove-1].getRange().getValue() & (int)pow(2,i) &&
                    this->entities[i] != nullptr)
                this->getComponent(i + 8)->draw(window);
        if(i<4)
            if(this->selectedMove == 5)
                if(this->entities[i])
                    this->getComponent(i + 8)->draw(window);
    }
    for(int i = 0; i < 8; i++){
        if(this->entities[i]){
            this->getComponent(i+16)->draw(window);
            this->getComponent(i+24)->getRectangleShape().setScale({(float)this->entities[i]->getHealth()/ (float)this->entities[i]->getMaxHealth(),1});
            this->getComponent(i+24)->draw(window);
        }
    }
    for(int i = 0; i < (int)this->animations.size(); i++){
        this->animations[i]->draw(window);
        if(dynamic_cast<Animation<sf::Text>*>(this->animations[i])->isDone()){
            delete this->animations[i];
            this->animations.erase(this->animations.begin() + i);
            i--;
        }
    }
    for(int i = 0; i < 8; i++){
        if(this->entities[i]){
            if(this->entities[i]->hasStatusEffect(STUN))
                this->getComponent(i+33)->draw(window);
        }
    }
    if(this->animations.empty() && this->delay <= 0)
        if(this->turnOrder.top() >= 4){
//        std::cout << "stuned:" << this->entities[this->turnOrder.top()]->hasStatusEffect(EffectType::STUN);
            if(this->entities[this->turnOrder.top()]->hasStatusEffect(EffectType::STUN)){
                auto* anim = new Animation<sf::Text>(0,8,5);
                anim->getSprite()->setString("Stuned");
                anim->getSprite()->setCharacterSize(42);
                anim->setMoves({{0,-42 * Settings::getInstance()->getScaleHeight()},
                                {0,-34 * Settings::getInstance()->getScaleHeight()},
                                {0,-26 * Settings::getInstance()->getScaleHeight()},
                                {0,-20 * Settings::getInstance()->getScaleHeight()},
                                {0,-15 * Settings::getInstance()->getScaleHeight()},
                                {0,-13 * Settings::getInstance()->getScaleHeight()},
                                {0,-8 * Settings::getInstance()->getScaleHeight()},
                                {0,-3 * Settings::getInstance()->getScaleHeight()},});
                anim->getSprite()->setPosition(FightScreen::getCoordsOfIndex(turnOrder.top())+ sf::Vector2f(20 * Settings::getInstance()->getScaleWidth(),
                                                                                                            80 * Settings::getInstance()->getScaleWidth()));
                anim->getSprite()->setFont(this->font);
                this->animations.push_back(anim);
            }else{
                sf::Vector2i move = dynamic_cast<EnemyAI*>(this->entities[this->turnOrder.top()])->getAttack(this->entities);
                if(move == sf::Vector2i(-1,-1)){
                    this->hasEnded = true;
                    return;
                }
                this->hit(&this->entities[turnOrder.top()]->getMoves()[move.x],move.y);
                this->entities[turnOrder.top()]->getSprite().reset();
            }
            this->endEntityTurn();
        } else {
            if(this->entities[turnOrder.top()]->hasStatusEffect(EffectType::STUN)){
                auto* anim = new Animation<sf::Text>(0,8,5);
                anim->getSprite()->setString("Stuned");
                anim->getSprite()->setCharacterSize(42);
                anim->setMoves({{0,-42 * Settings::getInstance()->getScaleHeight()},
                                {0,-34 * Settings::getInstance()->getScaleHeight()},
                                {0,-26 * Settings::getInstance()->getScaleHeight()},
                                {0,-20 * Settings::getInstance()->getScaleHeight()},
                                {0,-15 * Settings::getInstance()->getScaleHeight()},
                                {0,-13 * Settings::getInstance()->getScaleHeight()},
                                {0,-8 * Settings::getInstance()->getScaleHeight()},
                                {0,-3 * Settings::getInstance()->getScaleHeight()},});
                anim->getSprite()->setPosition(FightScreen::getCoordsOfIndex(turnOrder.top())+ sf::Vector2f(20 * Settings::getInstance()->getScaleWidth(),
                                                                                                            80 * Settings::getInstance()->getScaleWidth()));
                anim->getSprite()->setFont(this->font);
                this->animations.push_back(anim);
                this->endEntityTurn();
            }
        }
    this->mapPanel->draw(window);
//    if(this->characterPanel[this->selectedEntity]){
//        this->characterPanel[this->selectedEntity]->draw(window);
//    }
    this->characterPanel->draw(window);
}

FightScreen *FightScreen::getInstance() {
    if(FightScreen::singleton == nullptr)
        FightScreen::singleton = new FightScreen;
    return FightScreen::singleton;
}

int FightScreen::handleEvent(const sf::Event &event) {
//    if(this->characterPanel[this->selectedEntity])
//        if(this->characterPanel[this->selectedEntity]->handleEvent(event))
    this->characterPanel->handleEvent(event);
//            return true;
//    if(this->mapPanel->handleEvent(event))
//        return true;
    if(!this->visible)
        return 0;
    if(turnOrder.top() >= 4)
        return 0;
    if(event.type == sf::Event::KeyPressed){
        if(this->delay > 0)
            return 0;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) &&
           ((int)pow(2, turnOrder.top()) &
            this->entities[turnOrder.top()]->getMoves()[0].getCastPosition().getValue())){
            this->selectedMove = 1;
            return 1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) &&
           ((int)pow(2, turnOrder.top()) &
            this->entities[turnOrder.top()]->getMoves()[1].getCastPosition().getValue())){
            this->selectedMove = 2;
            return 2;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) &&
           ((int)pow(2, turnOrder.top()) &
            this->entities[turnOrder.top()]->getMoves()[2].getCastPosition().getValue())){
            this->selectedMove = 3;
            return 3;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) &&
           ((int)pow(2, turnOrder.top()) &
            this->entities[turnOrder.top()]->getMoves()[3].getCastPosition().getValue())){
            this->selectedMove = 4;
            return 4;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)){
            this->selectedMove = 5;
            return 5;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)){
            auto *animation = new Animation<sf::Text>(0,8,5);
            std::vector<sf::Vector2f> moves = {{0,-42 * Settings::getInstance()->getScaleHeight()},
                                               {0,-34 * Settings::getInstance()->getScaleHeight()},
                                               {0,-26 * Settings::getInstance()->getScaleHeight()},
                                               {0,-20 * Settings::getInstance()->getScaleHeight()},
                                               {0,-15 * Settings::getInstance()->getScaleHeight()},
                                               {0,-13 * Settings::getInstance()->getScaleHeight()},
                                               {0,-8 * Settings::getInstance()->getScaleHeight()},
                                               {0,-3 * Settings::getInstance()->getScaleHeight()},};
            animation->setMoves(moves);
            animation->getSprite()->setCharacterSize(42);
//            std::cout << turnOrder.top() << '\n';
            animation->getSprite()->setPosition(FightScreen::getCoordsOfIndex(turnOrder.top())+ sf::Vector2f(20 * Settings::getInstance()->getScaleWidth(),
                                                                                                             80 * Settings::getInstance()->getScaleWidth()));
            animation->getSprite()->setFont(this->font);
            animation->getSprite()->setString("Skip");
//            std::cout << "end turn\n";
            this->animations.push_back(animation);
            this->selectedMove = 6;
            this->endEntityTurn();
            return 6;
        }
    }
    if(event.type == sf::Event::MouseButtonPressed && this->delay <= 0){
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
                if (!(move->getRange().getValue() & (int)pow(2, i)))
                    continue;
                if(move->isAoe()){
                    for(int j = 0; j < 8; j++){
                        if((int)pow(2, j) & move->getRange().getValue())
                            this->hit(move,j);
                    }
                } else
                    this->hit(move, i);
                this->entities[turnOrder.top()]->getSprite().reset();
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
                    if(!this->entities[i])
                        continue;
                    this->swapEntities(i, this->turnOrder.top());
                    this->endEntityTurn();
                    return true;
                }catch(std::bad_cast&){}
            }
        }
    }
    return 0;
}

void FightScreen::turn() {
    if(this->turnOrder.empty()){
//        std::cout << "new turn\n";
        for(int i = 0; this->turnOrder.size() != 8; i++){
            for(int j = 0; j < 8; j++){
                if(this->entities[j] == nullptr)
                    continue;
                if(this->entities[j]->getStats().getValue(EffectType::SPEED) == i){
                    this->turnOrder.push(j);
//                    std::cout << this->turnOrder.top();
                }
            }
            if(i > 40)
                break;
        }
        if(this->turnOrder.top() < 4){
            this->selectedEntity = this->turnOrder.top();
            this->characterPanel->update(*this->entities[this->selectedEntity]);
        }
    }
}

void FightScreen::endEntityTurn() {
    this->delay = 60;
//    if(this->entities[turnOrder.top()] && this->selectedMove != 5 && this->selectedMove !=6)
//        this->entities[turnOrder.top()]->getSprite().reset();
    this->turnOrder.pop();
    this->selectedMove = 0;
    this->turn();
    while(!this->entities[turnOrder.top()]){
        this->turnOrder.pop();
        this->turn();
    }
    this->entities[turnOrder.top()]->turn();
    if(this->turnOrder.top() < 4){
        this->selectedEntity = turnOrder.top();
        this->characterPanel->update(*this->entities[this->selectedEntity]);

    }
}

void FightScreen::hit(Move *move, int index) {
    if(!this->entities[index])
        return;
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
    switch (ret) {
        case -1:
            animation = new Animation<sf::Text>(0,8,5);
            animation->setMoves(moves);
            animation->getSprite()->setString("Miss");
            animation->getSprite()->setCharacterSize(42);
            animation->getSprite()->setPosition(FightScreen::getCoordsOfIndex(index)+ sf::Vector2f(30 * Settings::getInstance()->getScaleWidth(),
                                                                                                   80 * Settings::getInstance()->getScaleWidth()));
            animation->getSprite()->setFont(this->font);
            this->animations.push_back(animation);
            break;
        case -2:
            animation = new Animation<sf::Text>(0,8,5);
            animation->setMoves(moves);
            animation->getSprite()->setString("Death");
            animation->getSprite()->setFillColor(sf::Color(255,10,20));
            animation->getSprite()->setCharacterSize(42);
            animation->getSprite()->setPosition(FightScreen::getCoordsOfIndex(index)+ sf::Vector2f(30 * Settings::getInstance()->getScaleWidth(),
                                                                                                   80 * Settings::getInstance()->getScaleWidth()));
            animation->getSprite()->setFont(this->font);
            this->animations.push_back(animation);
            this->deleteEntity(index);
            break;
        default:
            if(this->entities[index]->getHealth() <= 0) {
                animation = new Animation<sf::Text>(0,8,5);
                animation->setMoves(moves);
                animation->getSprite()->setString("Death's\nDoor");
                animation->getSprite()->setFillColor(sf::Color(255,10,20));
                animation->getSprite()->setCharacterSize(42);
                animation->getSprite()->setPosition(FightScreen::getCoordsOfIndex(index)+ sf::Vector2f(30 * Settings::getInstance()->getScaleWidth(),
                                                                                                       80 * Settings::getInstance()->getScaleWidth()));
                animation->getSprite()->setFont(this->font);
                this->animations.push_back(animation);
            }else{
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
            }
            if(ret > 0){
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
            }
    }
}

bool FightScreen::isDone() const {
    return this->hasEnded;
}
