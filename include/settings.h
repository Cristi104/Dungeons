#ifndef OOP_SETTINGS_H
#define OOP_SETTINGS_H

#include "SFML/Window.hpp"

class Settings {
private:
    static int resolutionWidth;
    static int resolutionHeight;
    static float scaleWidth;
    static float scaleHeight ;
public:
    static int getResolutionWidth() {
        return resolutionWidth;
    }

    static int getResolutionHeight() {
        return resolutionHeight;
    }

    static float getScaleWidth() {
        return scaleWidth;
    }

    static float getScaleHeight() {
        return scaleHeight;
    }
};
#endif //OOP_SETTINGS_H
