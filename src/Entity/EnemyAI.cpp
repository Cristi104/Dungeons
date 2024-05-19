//
// Created by cristi on 15.05.2024.
//

#include "../../include/Entity/EnemyAI.h"

EnemyAI::EnemyAI() {
    this->aggressiveness = 0;
}

void EnemyAI::update(Entity **fight, int currentPosition) {
    this->aggressiveness = this->aggressiveness * 0.5f;
    float aux = 0;
    for(int i = 0; i < 4; i++){
        if(fight[i]){
            aux += 0.9f - (float)fight[i]->getHealth() / (float)fight[i]->getMaxHealth() * 1.8f;
        } else {
            aux += 4;
        }
    }
    for(int i = 4; i < 8; i++){
        if(fight[i]){
            aux -= 0.75f - (float)fight[i]->getHealth() / (float)fight[i]->getMaxHealth() * 1.5f;
            if(i == currentPosition){
                aux -= 1.25f - (float)fight[i]->getHealth() / (float)fight[i]->getMaxHealth() * 2.5f;
            }
        } else {
            aux -= 3;
        }
    }
    this->aggressiveness += aux * 0.5f;
}
