#ifndef OOP_MOVE_H
#define OOP_MOVE_H

#include <string>
#include "../include/Positions.h"
#include "../include/StatusEffect.h"

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
    Move();
    Move(const Move& move);
    Move& operator=(const Move& move);
    ~Move() = default;
    friend std::ostream& operator<<(std::ostream& out, const Move& move);
    friend std::istream& operator>>(std::istream& in, Move& move);
    [[nodiscard]] const std::string &getName() const;
    [[nodiscard]] Positions getCastPosition() const;
    [[nodiscard]] Positions getRange() const;
    [[nodiscard]] int getAccuracy() const;
    [[nodiscard]] int getDamage() const;
    [[nodiscard]] const StatusEffect &getStatusEffect() const;
    [[nodiscard]] bool isAoe() const;
};

#endif //OOP_MOVE_H
