#include <valarray>
#include "../../include/Entity/Positions.h"

int Positions::getIndex() const {
    int i;
    int aux = this->value;
    for(i = 0; aux != 1; i++)aux /= 2;
    return i;
}

Positions::Positions(int value) {
    this->value = value;
}

int Positions::getValue() const {
    return (int)this->value;
}

