#ifndef OOP_ENTITY_H
#define OOP_ENTITY_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <string>
#include <vector>
#include <ostream>
#include <istream>
#include "../include/settings.h"

enum EffectType{
    SPEED = 1,
    ACCURACY = 2,
    STUN = 4,
    BLEED = 8,
    BURN = 16
};

enum Positions{
    BACKALLY1 = 1,
    BACKALLY2 = 2,
    FRONTALLY1 = 4,
    FRONTALLY2 = 8,
    BACKENEMY1 = 16,
    BACKENEMY2 = 32,
    FRONTENEMY1 = 64,
    FRONTENEMY2 = 128
};

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

class Move {
private:
    std::string name;
    Positions castPosition;
    Positions range;
    int accuracy;
    int damage;
    StatusEffect statusEffect;
    bool aoe;
public:
    Move();
    Move(const Move& move);
    Move& operator=(const Move& move);
    ~Move() = default;
    friend std::ostream& operator<<(std::ostream& out, const Move& move);
    friend std::istream& operator>>(std::istream& in, Move& move);
    [[nodiscard]] const std::string &getName() const;
    [[nodiscard]] Positions getCastPosition() const;
    [[nodiscard]] Positions getRange() const;
    [[nodiscard]] int getAccuracy() const;
    [[nodiscard]] int getDamage() const;
    [[nodiscard]] const StatusEffect &getStatusEffect() const;
    [[nodiscard]] bool isAoe() const;
};

class Stats{
private:
    int speed = 5;
    int accuracy = 100;
    int stun = 50;
    int bleed = 50;
    int burn = 50;
public:
    Stats() = default;
    Stats& operator=(const Stats& stats);
    ~Stats() = default;
    friend std::ostream& operator<<(std::ostream& out, const Stats& stats);
    friend std::istream& operator>>(std::istream& in, Stats& stats);
    [[nodiscard]] int getValue(EffectType type) const;
    void setValue(EffectType type, int value);
};

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
