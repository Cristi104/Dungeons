#ifndef OOP_MOVEPOPUP_H
#define OOP_MOVEPOPUP_H

#include "PopupPanel.h"
#include "../../Entity/Move.h"
#include "../Observer.h"

class MovePopup : public PopupPanel , public Observer<Move>{
private:
public:

    explicit MovePopup();

    void update(Move& move) override;

    ~MovePopup() override = default;
};

#endif //OOP_MOVEPOPUP_H
