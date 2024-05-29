#ifndef OOP_CHARACTERPANEL_H
#define OOP_CHARACTERPANEL_H

#include "Panel.h"
#include "../../Entity/Entity.h"
#include "../Observer.h"

class CharacterPanel : public Panel , public Observer<Entity>{
private:
    static Move* swap;
    static Move* skip;

public:

    explicit CharacterPanel();

    void update(Entity& entity) override;
};

#endif //OOP_CHARACTERPANEL_H
