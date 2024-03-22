#ifndef OOP_LABEL_H
#define OOP_LABEL_H

#include <SFML/Graphics/Text.hpp>
#include "Component.h"

class Label : public Component {
private:
    sf::Text text;
    static sf::Font font;
    void setText(const std::string& string, int maxLength);
public:
    static void initFont();
    Label();
    explicit Label(const std::string& text, int maxLength = 12);
    ~Label() override = default;
    void draw(sf::RenderWindow& window) override;
};

#endif //OOP_LABEL_H
