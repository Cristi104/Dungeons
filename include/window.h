#ifndef OOP_WINDOW_H
#define OOP_WINDOW_H

#include <SFML/Window.hpp>
#include <SFML/Graphics/Texture.hpp>
//#include <SFML/Graphics/Sprite.hpp>

#include <map>

class GameWindow {
private:
    sf::Window window;
    std::map<const std::string, sf::Texture> textures;
public:
    GameWindow();
    GameWindow(const std::string& name_p, int x_p, int y_p);
    ~GameWindow() = default;
    void loadTextures(const std::string& path_p);
    const sf::Texture& getTexture(const std::string& name_p);

};

#endif //OOP_WINDOW_H