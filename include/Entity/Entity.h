#ifndef OOP_ENTITY_H
#define OOP_ENTITY_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <string>
#include <ostream>
#include <istream>
#include "../Graphics/Settings.h"
#include "EffectType.h"
#include "Positions.h"
#include "Stats.h"
#include "StatusEffect.h"
#include "Move.h"
#include "../Graphics/Animation.h"

class Entity {
protected:
    Animation<sf::RectangleShape> sprite;
    std::string name;
    std::string textureName;
    Stats stats;
    int health;
    int maxHealth;
    int position;
    std::vector<StatusEffect> statusEffects;
    Move* moves;

public:

    Entity();

    Entity(const Entity& entity);

    Entity& operator=(const Entity& entity);

    virtual ~Entity();

    Animation<sf::RectangleShape>& getSprite();

    [[nodiscard]] const Stats &getStats() const;

    [[nodiscard]] Move *getMoves() const;

    [[nodiscard]] int getHealth() const;

    [[nodiscard]] int getMaxHealth() const;

    [[nodiscard]] const std::string &getName() const;

    [[nodiscard]] const std::string &getTextureName() const;

    void setPosition(int value);

    /// serializes the entity object
    friend std::ostream& operator<<(std::ostream& out, const Entity& entity);

    /// deserializes the entity object
    friend std::istream& operator>>(std::istream& in, Entity& entity);

    /// adds a StatusEffect object to the entity
    void applyStatusEffect(const StatusEffect& statusEffect);

    /// removes a StatusEffect form the entity
    void removeStatusEffect(int index);

    /// applies the effect of a move on the entity
    /// @return -1 if the move was dodged;
    /// @return 0 if the damage is applied
    /// @return EffectType if the status effect was applied
    int getHit(const Move& move);

    /// @return true if the entity has at least one status effect of the given type
    bool hasStatusEffect(EffectType effectType);

    /// decrements and deletes the StatusEffects applied to the entity every turn
    void turn();

    [[nodiscard]] int getPosition() const;
};

#endif //OOP_ENTITY_H
