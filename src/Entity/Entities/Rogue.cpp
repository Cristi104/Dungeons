//
// Created by cristi on 16.05.2024.
//

#include "../../../include/Entity/Entities/Rogue.h"
#include "../../../include/Graphics/GameWindow.h"

Rogue::Rogue() : Entity(){
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
    this->health = 17;
    this->maxHealth = 17;
    this->moves[0] = Move("Stab",
                          static_cast<Positions>(Positions::FRONTALLY2 | Positions::FRONTALLY1),
                          static_cast<Positions>(Positions::FRONTENEMY1 | Positions::FRONTENEMY2),
                          90, 7);
    this->moves[1] = Move("Throwing Dagger",
                          static_cast<Positions>(Positions::FRONTALLY1 | Positions::BACKALLY2),
                          static_cast<Positions>(Positions::FRONTENEMY1 | Positions::FRONTENEMY2 | Positions::BACKENEMY1 | Positions::BACKENEMY2),
                          85, 5, StatusEffect(), true);
    this->moves[2] = Move("Stab",
                          static_cast<Positions>(Positions::FRONTALLY2 | Positions::FRONTALLY1),
                          static_cast<Positions>(Positions::FRONTENEMY1 | Positions::FRONTENEMY2),
                          90, 7);
    this->moves[3] = Move("Stab",
                          static_cast<Positions>(Positions::FRONTALLY2 | Positions::FRONTALLY1),
                          static_cast<Positions>(Positions::FRONTENEMY1 | Positions::FRONTENEMY2),
                          90, 7);
    this->textureName = "Rogue";
    this->name = "Rogue";
    this->stats = Stats(7,100,50,80,10);
    this->sprite.getSprite()->setTexture(GameWindow::getTexture(this->textureName));

}
