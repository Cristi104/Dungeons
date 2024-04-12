#include "../../include/Map/BadMapGeneration.h"

BadMapGeneration::BadMapGeneration(const std::string &message) : runtime_error(message) {}

const char *BadMapGeneration::what() const noexcept {
    return runtime_error::what();
}
