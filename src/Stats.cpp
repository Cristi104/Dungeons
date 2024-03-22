#include "../include/Stats.h"

std::ostream& operator<<(std::ostream& out, const Stats& stats) {
    out << stats.speed << ' ' << stats.accuracy << ' ' << stats.stun << ' ' << stats.bleed << ' ' << stats.burn << ' ';
    return out;
}

std::istream& operator>>(std::istream& in, Stats& stats) {
    in >> stats.speed >> stats.accuracy >> stats.stun >> stats.bleed >> stats.burn;
    return in;
}

Stats& Stats::operator=(const Stats& stats) = default;

int Stats::getValue(EffectType type) const {
    switch (type) {
        case EffectType::SPEED:return this->speed;
        case EffectType::ACCURACY:return this->accuracy;
        case EffectType::STUN:return this->stun;
        case EffectType::BLEED:return this->bleed;
        case EffectType::BURN:return this->burn;
        default:return -1;
    }
}

void Stats::setValue(EffectType type, int value) {
    switch (type) {
        case EffectType::SPEED:this->speed = value;
            break;
        case EffectType::ACCURACY:this->accuracy = value;
            break;
        case EffectType::STUN:this->stun = value;
            break;
        case EffectType::BLEED:this->bleed = value;
            break;
        case EffectType::BURN:this->burn = value;
            break;
        default:return;
    }
}
