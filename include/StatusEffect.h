#ifndef OOP_STATUSEFFECT_H
#define OOP_STATUSEFFECT_H

#include <istream>
#include <ostream>
#include "../include/EffectType.h"

class StatusEffect {
private:
    EffectType type;
    int value;
    int duration;
    int chance;
public:
    StatusEffect();
    StatusEffect(EffectType type, int value, int duration, int chance);
    StatusEffect(const StatusEffect& statusEffect);
    StatusEffect& operator=(const StatusEffect& statusEffect);
    ~StatusEffect() = default;
    [[nodiscard]] EffectType getType() const;
    [[nodiscard]] int getValue() const;
    [[nodiscard]] int getDuration() const;
    [[nodiscard]] int getChance() const;
    int decrement();
    friend std::ostream& operator<<(std::ostream& out, const StatusEffect& effect);
    friend std::istream& operator>>(std::istream& in, StatusEffect& effect);
};

#endif //OOP_STATUSEFFECT_H
