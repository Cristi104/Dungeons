#include "../include/Game.h"
#include "../include/UserInterface/Panels/FightScreen.h"
#include "../include/Graphics/Animation.h"
#include "../include/Entity/EnemyFactory.h"
#include "../include/Entity/AllyFactory.h"

Game::Game() {
    this->panels.reserve(5);
    this->window = new GameWindow("Dungeons");
    this->running = true;
}

int Game::start() {
    EnemyFactory factoryE;
    AllyFactory factoryA;
    Entity* entity = factoryA.createEntity(0);
    FightScreen::getInstance()->addEntity(entity);
    FightScreen::getInstance()->swapEntities(0,3);
    FightScreen::getInstance()->addEntity(factoryA.createEntity(1));
    FightScreen::getInstance()->swapEntities(0,2);
    FightScreen::getInstance()->addEntity(factoryE.createEntity(0));
    FightScreen::getInstance()->swapEntities(7,4);
    FightScreen::getInstance()->addEntity(factoryE.createEntity(1));
    FightScreen::getInstance()->swapEntities(7,5);
    FightScreen::getInstance()->turn();
//    sf::View testView;

//    testView.reset({0,0,1200,700});
//    testView.setViewport({0,0,0.5,1});
//    Entity entity(0);
//    entity.getSprite().setMoves({{10, 10}, {10, 10}, {10, 10}, {10, 10}, {10, 10}});
//    entity.getSprite().getSprite().setTexture(GameWindow::getTexture("None"));
//    entity.getSprite().getSprite().setSize({100, 100});
    while(this->window->getWindow().isOpen() && running){
        sf::Event event{};
        while(this->window->getWindow().pollEvent(event)){
            bool wasHandled = false;
            if(!FightScreen::getInstance()->isDone())
                if(FightScreen::getInstance()->handleEvent(event)){
                    wasHandled = true;
                }
            for(int i = 0; i < (int)this->panels.size() && !wasHandled; i++) {
                if (panels[i]->handleEvent(event)) {
                    wasHandled = true;
                    break;
                }
            }
            if(!wasHandled){
                this->handleEvent(event);
            }
        }
        this->window->getWindow().clear();
//        window->getWindow().setView(testView);
        if(!FightScreen::getInstance()->isDone())
            FightScreen::getInstance()->draw(this->window->getWindow());
//        window->getWindow().setView(window->getWindow().getDefaultView());
//        entity.getSprite().draw(this->window->getWindow());
        this->window->getWindow().display();
    }
    GameWindow::freeTextures();
    return 0;
}

Game::~Game() {
    delete this->window;
    for(Panel* p : this->panels){
        delete p;
    }
}

bool Game::handleEvent(const sf::Event& event) {
    switch(event.type){
        case sf::Event::KeyPressed:
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                this->running = false;
                return true;
            }
            return false;
        default:
            return false;
    }
}
