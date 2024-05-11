#ifndef OOP_MOVE_H
#define OOP_MOVE_H

#include <string>
#include "Positions.h"
#include "StatusEffect.h"

class Move {
private:
    std::string name;
    Positions castPosition;
    Positions range;
    int accuracy;
    int damage;
    StatusEffect statusEffect;
    bool aoe;

public:

    /// creates a basic place holder move
    Move();

    Move(const std::string &name, Positions castPosition, Positions range, int accuracy, int damage,
         const StatusEffect &statusEffect = StatusEffect(), bool aoe = false);

    Move(const Move& move);

    Move& operator=(const Move& move);

    ~Move() = default;

    /// serializes the move data
    friend std::ostream& operator<<(std::ostream& out, const Move& move);

    /// deserializes the move data
    friend std::istream& operator>>(std::istream& in, Move& move);

    [[nodiscard]] const std::string &getName() const;

    [[nodiscard]] Positions getCastPosition() const;

    void setCastPosition(Positions positions);

    [[nodiscard]] Positions getRange() const;

    void setRange(Positions positions);

    [[nodiscard]] int getAccuracy() const;

    [[nodiscard]] int getDamage() const;

    [[nodiscard]] const StatusEffect &getStatusEffect() const;

    [[nodiscard]] bool isAoe() const;
};

#endif //OOP_MOVE_H
