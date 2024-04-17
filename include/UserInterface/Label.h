#ifndef OOP_LABEL_H
#define OOP_LABEL_H

#include <SFML/Graphics/Text.hpp>
#include "Component.h"

class Label : public Component {
private:
    sf::Text text;
    sf::Font font;
public:

    /// creates a Label of priority 3 and size 14 font
    explicit Label(int fontSize = 14, int priority = 3);

    /// creates a Label with text
    /// @param maxLength max number of characters on a line
    /// @param text text to display
    explicit Label(const std::string& text, int fontSize = 14, int maxLength = 12, int priority = 3);

    ~Label() override = default;

    /// draw the Label
    /// @param window draw target
    void draw(sf::RenderWindow& window) override;

    /// sets the text with automatic wrapping if it is longer than maxLength
    /// @param string new text
    /// @param maxLength wrap
    void setText(const std::string& string, int maxLength);

    /// sets the text without wrapping
    void setFormatedText(const std::string& string);

    void addPosition(sf::Vector2f position) override;
};

#endif //OOP_LABEL_H
