#include "../../include/Graphics/MissingTexture.h"

MissingTexture::MissingTexture(const std::string& message) : runtime_error(message) {}

const char *MissingTexture::what() const noexcept {
    return runtime_error::what();
}
