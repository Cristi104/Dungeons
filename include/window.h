#ifndef OOP_WINDOW_H
#define OOP_WINDOW_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
//#include <SFML/Graphics/Sprite.hpp>

#include <map>

class GameWindow : public sf::RenderWindow{
private:
    std::map<const std::string, sf::Texture> textures;
public:
    GameWindow();
    GameWindow(const std::string& name_p, int x_p, int y_p);
    ~GameWindow() override;
    void loadTextures(const std::string& path_p);
    const sf::Texture& getTexture(const std::string& name_p);

};

#endif //OOP_WINDOW_H