#ifndef OOP_SETTINGS_H
#define OOP_SETTINGS_H

#include "SFML/Window.hpp"

class Settings {
private:
    int resolutionWidth;
    int resolutionHeight;
    float scaleWidth;
    float scaleHeight ;
    static Settings* singleton;
    Settings();
public:
    [[nodiscard]] int getResolutionWidth() const;

    [[nodiscard]] int getResolutionHeight() const;

    [[nodiscard]] float getScaleWidth() const;

    [[nodiscard]] float getScaleHeight() const;

    static Settings *getSingleton();
};
#endif //OOP_SETTINGS_H
