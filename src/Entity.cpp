#include "../include/Entity.h"
#include <random>

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
