#include "../include/entity.h"
#include <random>

//StatusEffect
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

//Move
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

//Stats
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

//Entity
Entity::Entity() {
    this->moves = new Move[4];
    this->name = "None";
    this->textureName = "None";
    this->health = 0;
    this->maxHealth = 0;
    this->position = static_cast<Positions>(0);
    this->statusEffects.resize(0);
}

Entity::Entity(const Entity &entity) {
    this->sprite = entity.sprite;
    this->name = entity.name;
    this->textureName = entity.textureName;
    this->moves = new Move[4];
    for(int i = 0; i < 4; i++)
        this->moves[i] = entity.moves[i];
    this->health = entity.health;
    this->maxHealth = entity.maxHealth;
    this->position = entity.position;
    this->statusEffects = entity.statusEffects;
}

Entity &Entity::operator=(const Entity &entity) {
    this->sprite = entity.sprite;
    this->name = entity.name;
    this->textureName = entity.textureName;
    this->stats = entity.stats;
    this->health = entity.health;
    this->maxHealth = entity.maxHealth;
    this->position = entity.position;
    this->statusEffects = entity.statusEffects;
    for(int i = 0; i < 4; i++)
        this->moves[i] = entity.moves[i];
    return *this;
}

Entity::~Entity() {
    delete[] this->moves;
}

sf::RectangleShape& Entity::getRectangleShape() {
    return this->sprite;
}

std::ostream& operator<<(std::ostream& out, const Entity& entity) {
    out << entity.name << '\n' << entity.textureName << '\n' << entity.stats << entity.health << ' ' << entity.maxHealth << ' ' << static_cast<int>(entity.position) << '\n';
    out << entity.statusEffects.size() << '\n';
    for(const StatusEffect& effect : entity.statusEffects)
        out << effect;
    for(int i = 0; i < 4; i++)
        out << entity.moves[i];
    return out;
}

std::istream& operator>>(std::istream& in, Entity& entity) {
    int x;
    in >> entity.name >> entity.textureName >> entity.stats >> entity.health >> entity.maxHealth >> x;
    entity.position = static_cast<Positions>(x);
    in >> x;
    entity.statusEffects.resize(x);
    for(StatusEffect& effect : entity.statusEffects)
        in >> effect;
    for(int i = 0; i < 4; i++)
        in >> entity.moves[i];
    return in;
}

void Entity::applyStatusEffect(const StatusEffect& statusEffect) {
    this->statusEffects.push_back(statusEffect);
    this->stats.setValue(statusEffect.getType(),
                         this->stats.getValue(statusEffect.getType())
                         - statusEffect.getValue());
}

void Entity::removeStatusEffect(int index) {
    this->stats.setValue(statusEffects[index].getType(),
                         this->stats.getValue(statusEffects[index].getType())
                         + statusEffects[index].getValue());
    statusEffects.erase(std::next(statusEffects.begin(),index));
}

void Entity::getHit(const Move& move) {
    std::random_device device;
    std::mt19937 gen(device());
    std::uniform_int_distribution<> random(1,100);
    if(random(gen) - move.getAccuracy() <= 0) {
        int statusEffectChance = move.getStatusEffect().getChance()
                - this->stats.getValue(move.getStatusEffect().getType());
        if(random(gen) - statusEffectChance <= 0){
            this->applyStatusEffect(move.getStatusEffect());
        }
        this->health = (this->health + move.getDamage() < this->maxHealth)? this->health + move.getDamage() : this->maxHealth;
    }
}

void Entity::turn() {
    int n = (int)this->statusEffects.size();
    for(int i = 0; i < n;) {
        this->health -= statusEffects[i].getValue();
        if(!statusEffects[i].decrement()){
            i++;
        }else{
            this->removeStatusEffect(i);
            n--;
        }
    }
}

Positions Entity::getPosition() const {
    return position;
}
