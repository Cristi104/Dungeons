//
// Created by cristi on 16.05.2024.
//

#include "../../../include/Entity/Entities/Knight.h"
#include "../../../include/Graphics/GameWindow.h"

Knight::Knight() : Entity(){
    this->sprite.setMoves({{15 * Settings::getInstance()->getScaleWidth(), 0},
                           {12 * Settings::getInstance()->getScaleWidth(), 0},
                           {10 * Settings::getInstance()->getScaleWidth(), 0},
                           {7 * Settings::getInstance()->getScaleWidth(), 0},
                           {4 * Settings::getInstance()->getScaleWidth(), 0},
                           {2 * Settings::getInstance()->getScaleWidth(), 0},
                           {-6 * Settings::getInstance()->getScaleWidth(), 0},
                           {-8 * Settings::getInstance()->getScaleWidth(), 0},
                           {-11 * Settings::getInstance()->getScaleWidth(), 0},
                           {-25 * Settings::getInstance()->getScaleWidth(), 0}});
    this->position = 0;
    this->health = 10;
    this->maxHealth = 20;
    this->moves[0] = Move("Shield Bash",
                          static_cast<Positions>(Positions::FRONTALLY2),
                          static_cast<Positions>(Positions::FRONTENEMY1 | Positions::FRONTENEMY2),
                          95, 4, StatusEffect(EffectType::STUN, 1, 100, 0));
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
    this->sprite.getSprite()->setTexture(GameWindow::getTexture(this->textureName));
}
