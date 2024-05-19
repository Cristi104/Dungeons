//
// Created by cristi on 16.05.2024.
//

#include <random>
#include "../../../include/Entity/Entities/Skeleton.h"
#include "../../../include/Graphics/GameWindow.h"

Skeleton::Skeleton() : Entity(){
    this->sprite.setMoves({{-15 * Settings::getInstance()->getScaleWidth(), 0},
                           {-12 * Settings::getInstance()->getScaleWidth(), 0},
                           {-10 * Settings::getInstance()->getScaleWidth(), 0},
                           {-7 * Settings::getInstance()->getScaleWidth(), 0},
                           {-4 * Settings::getInstance()->getScaleWidth(), 0},
                           {-2 * Settings::getInstance()->getScaleWidth(), 0},
                           {6 * Settings::getInstance()->getScaleWidth(), 0},
                           {8 * Settings::getInstance()->getScaleWidth(), 0},
                           {11 * Settings::getInstance()->getScaleWidth(), 0},
                           {25 * Settings::getInstance()->getScaleWidth(), 0}});
    this->position = 0;
    this->health = 20;
    this->maxHealth = 20;
    this->moves[0] = Move("Shield Bash",
                          static_cast<Positions>(Positions::FRONTENEMY2 | Positions::FRONTENEMY1),
                          static_cast<Positions>(Positions::FRONTALLY1 | Positions::FRONTALLY2 | Positions::BACKALLY2),
                          90, 4, StatusEffect(EffectType::STUN, 1, 100, 0));
    this->moves[1] = Move("Stab",
                          static_cast<Positions>(Positions::FRONTENEMY2 | Positions::FRONTENEMY1),
                          static_cast<Positions>(Positions::FRONTALLY1 | Positions::FRONTALLY2),
                          100, 7);
    this->moves[2] = Move("Scramble",
                          static_cast<Positions>(Positions::FRONTENEMY2 | Positions::FRONTENEMY1 | Positions::BACKENEMY2 | Positions::BACKENEMY1),
                          static_cast<Positions>(Positions::FRONTALLY1 | Positions::FRONTALLY2),
                          80, 5);
    this->textureName = "Skeleton";
    this->name = "Skeleton";
    this->stats = Stats(2,100,50,80,10);
    this->sprite.getSprite()->setTexture(GameWindow::getTexture(this->textureName));

}

sf::Vector2i Skeleton::getAttack(Entity** fight) {
    this->update(fight, this->position);
    sf::Vector2i move;
    std::random_device device;
    std::mt19937 gen(device());
    std::uniform_int_distribution<> random(-10,10);
    if(random(gen) < (int)this->aggressiveness){
        move.x = 0;
    } else {
        move.x = 1;
    }
    int min = 100;
    for(int i = 1; i < 128; i*=2){
        if(fight[Positions(i).getIndex()] && this->moves[move.x].getRange().getValue() & i && (random(gen) < 0 || min == 100)){
            if(fight[Positions(i).getIndex()]->getHealth() < min){
                move.y = Positions(i).getIndex();
                min = fight[Positions(i).getIndex()]->getHealth();
            }
        }
    }
    if(!(this->position & this->moves[move.x].getCastPosition().getIndex()) || min == 100){
        move.x = 2;
        for(int i = 1; i < 128; i*=2){
            if(fight[Positions(i).getIndex()] && this->moves[move.x].getRange().getValue() & i && (random(gen) < 0 || min == 100)){
                if(fight[Positions(i).getIndex()]->getHealth() < min){
                    move.y = Positions(i).getIndex();
                    min = fight[Positions(i).getIndex()]->getHealth();
                }
            }
        }
    }
    return move;
}
