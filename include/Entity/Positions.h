#ifndef OOP_POSITIONS_H
#define OOP_POSITIONS_H

class Positions{
private:
    int value;
public:
    enum V{
        BACKALLY1 = 1,
        BACKALLY2 = 2,
        FRONTALLY1 = 4,
        FRONTALLY2 = 8,
        FRONTENEMY1 = 16,
        FRONTENEMY2 = 32,
        BACKENEMY1 = 64,
        BACKENEMY2 = 128,
    };
    [[nodiscard]] int getIndex() const;
    [[nodiscard]] int getValue() const;
    explicit Positions(int value = 0);
};
#endif //OOP_POSITIONS_H
