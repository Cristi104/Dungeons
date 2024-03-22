#include "../include/StatusEffect.h"

StatusEffect::StatusEffect() {
    this->type = static_cast<EffectType>(0);
    this->value = 0;
    this->duration = 0;
    this->chance = 0;
}

StatusEffect::StatusEffect(EffectType type, int value, int duration, int chance) {
    this->type = type;
    this->value = value;
    this->duration = duration;
    this->chance = chance;
}

StatusEffect::StatusEffect(const StatusEffect& statusEffect) {
    this->type = statusEffect.type;
    this->value = statusEffect.value;
    this->duration = statusEffect.duration;
    this->chance = statusEffect.chance;
}

StatusEffect& StatusEffect::operator=(const StatusEffect& statusEffect) = default;

EffectType StatusEffect::getType() const {
    return type;
}

int StatusEffect::getValue() const {
    return value;
}

int StatusEffect::getDuration() const {
    return duration;
}

int StatusEffect::getChance() const {
    return chance;
}

int StatusEffect::decrement() {
    if(duration > 0)
        duration--;
    return duration;
}

std::ostream& operator<<(std::ostream& out, const StatusEffect& effect) {
    out << static_cast<int>(effect.type) << ' ' << effect.value << ' ' << effect.duration << ' ' << effect.chance << ' ';
    return out;
}

std::istream& operator>>(std::istream& in, StatusEffect& effect) {
    int x;
    in >> x >> effect.value >> effect.duration >> effect.chance;
    effect.type = static_cast<EffectType>(x);
    return in;
}
