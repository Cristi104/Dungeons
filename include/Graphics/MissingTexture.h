#ifndef OOP_MISSINGTEXTURE_H
#define OOP_MISSINGTEXTURE_H
#include <stdexcept>

class MissingTexture : public std::runtime_error{
public:
    explicit MissingTexture(const std::string& message);
    [[nodiscard]] const char* what() const noexcept override;
};


#endif //OOP_MISSINGTEXTURE_H
