#ifndef OOP_STATS_H
#define OOP_STATS_H

#include <istream>
#include <ostream>
#include "EffectType.h"

class Stats{
private:
    int speed = 5;
    int accuracy = 100;
    int stun = 50;
    int bleed = 50;
    int burn = 50;
public:

    /// creates a basic stats object
    Stats() = default;

    Stats(int speed, int accuracy, int stun, int bleed, int burn);

    Stats& operator=(const Stats& stats);

    ~Stats() = default;

    /// serializes the stats data
    friend std::ostream& operator<<(std::ostream& out, const Stats& stats);

    /// deserializes the stats data
    friend std::istream& operator>>(std::istream& in, Stats& stats);

    /// get effect data
    /// @param type stat type
    [[nodiscard]] int getValue(EffectType type) const;

    /// set the value of a stat
    /// @param type stat type
    /// @param value new value
    void setValue(EffectType type, int value);
};

#endif //OOP_STATS_H
