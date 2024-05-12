#ifndef OOP_GAME_H
#define OOP_GAME_H

#include "UserInterface/Panels/Panel.h"

class Game {
private:
    std::vector<Panel*> panels;
    GameWindow* window;
    bool running;
    bool handleEvent(const sf::Event& event);

public:

    Game();

    Game(const Game& game) = delete;

    Game& operator=(const Game& game) = delete;

    ~Game();

    int start();
};

#endif //OOP_GAME_H
