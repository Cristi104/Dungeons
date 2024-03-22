#ifndef OOP_STATS_H
#define OOP_STATS_H

#include <istream>
#include <ostream>
#include "../include/EffectType.h"

class Stats{
private:
    int speed = 5;
    int accuracy = 100;
    int stun = 50;
    int bleed = 50;
    int burn = 50;
public:
    Stats() = default;
    Stats& operator=(const Stats& stats);
    ~Stats() = default;
    friend std::ostream& operator<<(std::ostream& out, const Stats& stats);
    friend std::istream& operator>>(std::istream& in, Stats& stats);
    [[nodiscard]] int getValue(EffectType type) const;
    void setValue(EffectType type, int value);
};

#endif //OOP_STATS_H
