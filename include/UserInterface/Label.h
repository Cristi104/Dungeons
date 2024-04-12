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

    /// Loads global font
    static void initFont();

    /// creates a Label of priority 3 and size 12 font
    Label();

    /// creates a Label with text
    /// @param maxLength max number of characters on a line
    /// @param text text to display
    explicit Label(const std::string& text, int maxLength = 12);

    ~Label() override = default;

    /// draw the Label
    /// @param window draw target
    void draw(sf::RenderWindow& window) override;
};

#endif //OOP_LABEL_H
