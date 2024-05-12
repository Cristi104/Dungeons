#include "../../include/Entity/Entity.h"
#include <random>
#include "../../include/Graphics/GameWindow.h"

Entity::Entity() {
    this->moves = new Move[4];
    this->name = "None";
    this->textureName = "None";
    this->health = 0;
    this->maxHealth = 0;
    this->position = 1;
    this->statusEffects.resize(0);
    this->sprite.setSize({120 * Settings::getInstance()->getScaleWidth(),
                          200 * Settings::getInstance()->getScaleHeight()});
    this->sprite.setTexture(GameWindow::getTexture(this->textureName));
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
    this->stats = entity.stats;
}

Entity &Entity::operator=(const Entity &entity) {
    if(&entity == this) return *this;
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
    this->stats = entity.stats;
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
        int statusEffectChance = move.getStatusEffect().getChance() - this->stats.getValue(move.getStatusEffect().getType());
        if(random(gen) - statusEffectChance <= 0){
            this->applyStatusEffect(move.getStatusEffect());
        }
        this->health = (this->health - move.getDamage() < this->maxHealth)? this->health - move.getDamage() : this->maxHealth;
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

int Entity::getPosition() const {
    return position;
}

const Stats &Entity::getStats() const {
    return stats;
}

Move *Entity::getMoves() const {
    return moves;
}

Entity::Entity(int id) {
    this->moves = new Move[4];
    this->sprite.setSize({120 * Settings::getInstance()->getScaleWidth(),
                          200 * Settings::getInstance()->getScaleHeight()});
    this->position = 0;
    switch (id) {
        case 0://knight
            this->health = 10;
            this->maxHealth = 20;
            this->moves[0] = Move("Shield Bash",
                                  static_cast<Positions>(Positions::FRONTALLY2),
                                  static_cast<Positions>(Positions::FRONTENEMY1 | Positions::FRONTENEMY2),
                                  95, 4, StatusEffect(EffectType::STUN, 1, 50, 0));
            this->moves[1] = Move("Holy Lance",
                                  static_cast<Positions>(Positions::BACKALLY2 | Positions::BACKALLY1),
                                  static_cast<Positions>(Positions::FRONTENEMY1 | Positions::FRONTENEMY2 | Positions::BACKENEMY1),
                                  85, 9);
            this->moves[2] = Move("Stab",
                                  static_cast<Positions>(Positions::FRONTALLY2 | Positions::FRONTALLY1),
                                  static_cast<Positions>(Positions::FRONTENEMY1 | Positions::FRONTENEMY2),
                                  90, 7);
            this->moves[3] = Move("Bandage Wounds",
                                  static_cast<Positions>(Positions::FRONTALLY2),
                                  static_cast<Positions>(Positions::FRONTALLY2),
                                  200, -4);
            this->textureName = "Knight";
            this->name = "Knight";
            this->stats = Stats(3,100,50,80,10);
            this->sprite.setTexture(GameWindow::getTexture(textureName));
            break;
        case 1://rogue
            this->health = 15;
            this->maxHealth = 15;
            this->moves[0] = Move("Shield Bash",
                                  static_cast<Positions>(Positions::FRONTALLY2),
                                  static_cast<Positions>(Positions::FRONTENEMY1 | Positions::FRONTENEMY2),
                                  95, 4, StatusEffect(EffectType::STUN, 1, 50));
            this->moves[1] = Move("Holy Lance",
                                  static_cast<Positions>(Positions::BACKALLY2 | Positions::BACKALLY1),
                                  static_cast<Positions>(Positions::FRONTENEMY1 | Positions::FRONTENEMY2 | Positions::BACKENEMY1),
                                  85, 9);
            this->moves[2] = Move("Stab",
                                  static_cast<Positions>(Positions::FRONTALLY2 | Positions::FRONTALLY1),
                                  static_cast<Positions>(Positions::FRONTENEMY1 | Positions::FRONTENEMY2),
                                  90, 7);
            this->moves[3] = Move("Bandage Wounds",
                                  static_cast<Positions>(Positions::FRONTALLY2),
                                  static_cast<Positions>(Positions::FRONTALLY2),
                                  200, -4);
            this->textureName = "Rogue";
            this->name = "Rogue";
            this->stats = Stats(7,100,30,40,20);
            this->sprite.setTexture(GameWindow::getTexture(textureName));
            break;
        default:
            throw(std::out_of_range("entity id out of range.\n"));
    }
}

int Entity::getHealth() const {
    return health;
}

int Entity::getMaxHealth() const {
    return maxHealth;
}

const std::string &Entity::getName() const {
    return name;
}

const std::string &Entity::getTextureName() const {
    return textureName;
}
