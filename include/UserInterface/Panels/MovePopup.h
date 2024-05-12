#ifndef OOP_MOVEPOPUP_H
#define OOP_MOVEPOPUP_H

#include "PopupPanel.h"
#include "../../Entity/Move.h"

class MovePopup : public PopupPanel{
private:
    const Move* move;

public:

    explicit MovePopup(const Move* move);

    ~MovePopup() override = default;
};

#endif //OOP_MOVEPOPUP_H
