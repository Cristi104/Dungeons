#include "../include/Move.h"

Move::Move() {
    this->name = "None";
    this->castPosition = static_cast<Positions>(0);
    this->range = static_cast<Positions>(0);
    this->accuracy = 100;
    this->damage = 0;
    this->aoe = false;
}

Move::Move(const Move& move) {
    this->name = move.name;
    this->castPosition = move.castPosition;
    this->range = move.range;
    this->accuracy = move.accuracy;
    this->damage = move.damage;
    this->aoe = move.aoe;
    this->statusEffect = move.statusEffect;
}

Move& Move::operator=(const Move& move) = default;

std::ostream& operator<<(std::ostream& out, const Move& move) {
    out << move.name << '\n' << static_cast<int>(move.castPosition) << ' ' << static_cast<int>(move.range) << ' ' << move.accuracy << ' ' << move.damage << ' ' << move.statusEffect << move.aoe << '\n';
    return out;
}

std::istream& operator>>(std::istream& in, Move& move) {
    int x,y;
    in >> move.name >> x >> y >> move.accuracy >> move.damage >> move.statusEffect >> move.aoe;
    move.castPosition = static_cast<Positions>(x);
    move.range = static_cast<Positions>(y);
    return in;
}

const std::string& Move::getName() const {
    return name;
}

Positions Move::getCastPosition() const {
    return castPosition;
}

Positions Move::getRange() const {
    return range;
}

int Move::getAccuracy() const {
    return accuracy;
}

int Move::getDamage() const {
    return damage;
}

const StatusEffect& Move::getStatusEffect() const {
    return statusEffect;
}

bool Move::isAoe() const {
    return aoe;
}
