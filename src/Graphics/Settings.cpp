#include "../../include/Graphics/Settings.h"
//
//int Settings::resolutionWidth = (int)sf::VideoMode::getDesktopMode().width;
//int Settings::resolutionHeight = (int)sf::VideoMode::getDesktopMode().height;
//float Settings::scaleWidth = (float)Settings::resolutionWidth / 1280.0f;
//float Settings::scaleHeight = (float)Settings::resolutionWidth / 720.0f;
//
//int Settings::resolutionWidth = 1920;
//int Settings::resolutionHeight = 1080;
//float Settings::scaleWidth = (float)Settings::resolutionWidth / 1280.0f;
//float Settings::scaleHeight = (float)Settings::resolutionWidth / 720.0f;

Settings* Settings::singleton = nullptr;

Settings::Settings() {
    this->resolutionHeight = (int)sf::VideoMode::getDesktopMode().height;
    this->resolutionWidth = (int)sf::VideoMode::getDesktopMode().width;
    this->scaleWidth = (float)Settings::resolutionWidth / 1280.0f;
    this->scaleHeight = (float)Settings::resolutionHeight / 720.0f;
}

int Settings::getResolutionWidth() const {
    return resolutionWidth;
}

int Settings::getResolutionHeight() const {
    return resolutionHeight;
}

float Settings::getScaleWidth() const {
    return scaleWidth;
}

float Settings::getScaleHeight() const {
    return scaleHeight;
}

Settings *Settings::getInstance() {
    if(Settings::singleton == nullptr)
        Settings::singleton = new Settings;
    return Settings::singleton;
}
