#ifndef OOP_ENTITY_H
#define OOP_ENTITY_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <string>
#include <ostream>
#include <istream>
#include "Settings.h"
#include "EffectType.h"
#include "Positions.h"
#include "Stats.h"
#include "StatusEffect.h"
#include "Move.h"

class Entity {
private:
    sf::RectangleShape sprite;
    std::string name;
    std::string textureName;
    Stats stats;
    int health;
    int maxHealth;
    Positions position;
    std::vector<StatusEffect> statusEffects;
    Move* moves;
public:
    Entity();
    Entity(const Entity& entity);
    Entity& operator=(const Entity& entity);
    ~Entity();
    sf::RectangleShape& getRectangleShape();
    friend std::ostream& operator<<(std::ostream& out, const Entity& entity);
    friend std::istream& operator>>(std::istream& in, Entity& entity);
    void applyStatusEffect(const StatusEffect& statusEffect);
    void removeStatusEffect(int index);
    void getHit(const Move& move);
    void turn();
    Positions getPosition() const;
};

#endif //OOP_ENTITY_H
