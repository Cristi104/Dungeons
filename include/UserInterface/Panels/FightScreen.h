#ifndef OOP_FIGHTSCREEN_H
#define OOP_FIGHTSCREEN_H

#include <stack>
#include "../../Entity/Entity.h"
#include "Panel.h"
#include "../../Graphics/GameWindow.h"
#include "../../Map/Map.h"
#include "CharacterPanel.h"

class FightScreen :public Panel{
private:
    Entity** entities;
    static FightScreen* singleton;
    std::stack<int> turnOrder;
    int selectedMove;
    int selectedEntity;
    CharacterPanel* characterPanel;
    Panel* mapPanel;
    Map* currentMap;
    std::vector<Drawn*> animations;
    sf::Font font;
    int delay;
    bool hasEnded;

    /// conversion from entity index to screen coordinates
    /// @return top left corner coordinates
    static sf::Vector2f getCoordsOfIndex(int index);

    void hit(Move* move, int index);

    FightScreen();
public:

    ~FightScreen() override;

    /// adds an entity to the FightScreen
    /// @param entity pointer to a heap allocated Entity object
    void addEntity(Entity* entity);

    /// swaps 2 entities
    /// @param index1 index of first entity
    /// @param index2 index of second entity
    void swapEntities(int index1, int index2);

    /// delete entity at a index
    /// @param index index of entity object
    void deleteEntity(int index);

    void draw(sf::RenderWindow& window) override;

    int handleEvent(const sf::Event& event) override;

    /// recreates the turnOrder if it is empty
    void turn();

    ///handles the ending of an entity's turn
    void endEntityTurn();

    bool isDone() const;

    static FightScreen *getInstance();
};

#endif //OOP_FIGHTSCREEN_H
