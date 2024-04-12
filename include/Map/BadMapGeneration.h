#ifndef OOP_BADMAPGENERATION_H
#define OOP_BADMAPGENERATION_H

#include <stdexcept>

class BadMapGeneration : public std::runtime_error{
public:
    explicit BadMapGeneration(const std::string& message);
    [[nodiscard]] const char* what() const noexcept override;
};


#endif //OOP_BADMAPGENERATION_H
