#ifndef OOP_CHARACTERPANEL_H
#define OOP_CHARACTERPANEL_H

#include "Panel.h"
#include "../../Entity/Entity.h"

class CharacterPanel : public Panel{
private:
    Entity* entity;

public:

    explicit CharacterPanel(Entity* entity);

    void update();
};

#endif //OOP_CHARACTERPANEL_H
