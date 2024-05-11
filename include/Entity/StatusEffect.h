#ifndef OOP_STATUSEFFECT_H
#define OOP_STATUSEFFECT_H

#include <istream>
#include <ostream>
#include "EffectType.h"

class StatusEffect {
private:
    EffectType type;
    int value;
    int duration;
    int chance;
public:

    /// creates a place holder effect
    StatusEffect();

    /// creates a completely defined status effect
    /// @param type the type of effect
    /// @param duration number of turns the entity has this effect
    /// @param chance percent chance that the effect is applied
    /// @param value amount of healing/damage/deBuff
    StatusEffect(EffectType type, int duration, int chance, int value = 0);

    StatusEffect(const StatusEffect& statusEffect);

    StatusEffect& operator=(const StatusEffect& statusEffect);

    ~StatusEffect() = default;

    [[nodiscard]] EffectType getType() const;

    [[nodiscard]] int getValue() const;

    [[nodiscard]] int getDuration() const;

    [[nodiscard]] int getChance() const;

    /// pass a turn
    int decrement();

    /// serializes the effect data
    friend std::ostream& operator<<(std::ostream& out, const StatusEffect& effect);

    /// deserializes the effect data
    friend std::istream& operator>>(std::istream& in, StatusEffect& effect);
};

#endif //OOP_STATUSEFFECT_H
