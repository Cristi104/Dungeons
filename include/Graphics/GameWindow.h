#ifndef OOP_GAMEWINDOW_H
#define OOP_GAMEWINDOW_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Settings.h"
//#include <SFML/Graphics/RectangleShape.hpp>

#include <map>

class GameWindow {
private:
    sf::RenderWindow window;
    static std::map<const std::string, sf::Texture*> textures;
public:

    /// Creates a default 1200/720 window and loads textures.
    GameWindow();


    /// Crates a fullscreen window and loads textures
    /// @param name name of window
    /// @param x width of window
    /// @param y height of window
    explicit GameWindow(const std::string& name,
                        int x = Settings::getSingleton()->getResolutionWidth(),
                        int y = Settings::getSingleton()->getResolutionHeight());

    /// @param path path to the folder from witch to load textures
    ~GameWindow();

    /// @param name name of texture without .png!
    /// @return a pointer to the texture
    /// @throw MissingTexture when the wanted texture is not found
    static void loadTextures(const std::string& path);

    static const sf::Texture* getTexture(const std::string& name);

    /// call at the end of the program to free dynamic textures allocated inside static members
    static void freeTextures();

    /// @return a reference to the drawing window
    sf::RenderWindow& getWindow();

};

#endif //OOP_GAMEWINDOW_H