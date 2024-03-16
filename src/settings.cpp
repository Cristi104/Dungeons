#include "../include/settings.h"

int Settings::resolutionWidth = (int)sf::VideoMode::getDesktopMode().width;
int Settings::resolutionHeight = (int)sf::VideoMode::getDesktopMode().height;
float Settings::scaleWidth = (float)Settings::resolutionWidth / 1280.0f;
float Settings::scaleHeight = (float)Settings::resolutionWidth / 720.0f;
