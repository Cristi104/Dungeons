#include <random>
#include <queue>
#include "../../include/Map/Map.h"
#include "../../include/Map/BadMapGeneration.h"

Map::Map(const Biome &biome) {
    this->size = biome.getSize();
    this->map = new nod*[this->size.y];
    for(int i = 0; i < this->size.y; i++)
        this->map[i] = new nod[this->size.x];
    std::random_device device;
    std::mt19937 gen(device());
    std::uniform_int_distribution<> random(1,100);
    sf::Vector2i position(this->size.x / 2, this->size.y / 2);
    this->map[this->size.x / 2][this->size.y / 2].room = new Room(MapEvent::NoEvent);
    int roomNumber = biome.getLengthMin() + random(gen) % (biome.getLengthMax()-biome.getLengthMin());
    for(int i = 1; i< roomNumber; i++){
        if(random(gen) > biome.getBranchingChance()){
            int branchSize = random(gen) % ((roomNumber - i) / 2 + 1);
            if(branchSize){
                this->extend(biome, position, branchSize);
            }
            i += branchSize;
        }
        position = this->extend(biome, position);
    }
    this->texture.create(
            this->size.x * 32 + (this->size.x - 1) * 8 * biome.getRoadLengthMax() + 32,
            this->size.y * 32 + (this->size.y - 1) * 8 * biome.getRoadLengthMax() + 32);
    this->texture.clear(sf::Color(11,16,0));

    sf::RectangleShape roomHelperSprite;
    roomHelperSprite.setTexture(GameWindow::getTexture("Room"));
    roomHelperSprite.setSize(sf::Vector2f(32,32));
    sf::RectangleShape roadHelperSpriteVertical;
    roadHelperSpriteVertical.setTexture(GameWindow::getTexture("Road"));
    roadHelperSpriteVertical.setTextureRect(sf::IntRect(0,0,biome.getRoadLengthMax()*4,4));
    roadHelperSpriteVertical.rotate(90);
    roadHelperSpriteVertical.setSize(sf::Vector2f((float)(8 * biome.getRoadLengthMax()),8));
    sf::RectangleShape roadHelperSpriteHorizontal;
    roadHelperSpriteHorizontal.setTexture(GameWindow::getTexture("Road"));
    roadHelperSpriteHorizontal.setTextureRect(sf::IntRect(0,0,biome.getRoadLengthMax()*4,4));
    roadHelperSpriteHorizontal.setSize(sf::Vector2f((float)(8 * biome.getRoadLengthMax()), 8));

    for(int i = 0; i < this->size.y; i++){
        for(int j = 0; j < this->size.x; j++){
            if(map[i][j].room){
                roomHelperSprite.setPosition(
                        (float)(j * (32 + 8 * biome.getRoadLengthMax()) + 16),
                        (float)(i * (32 + 8 * biome.getRoadLengthMax()) + 16));
                this->texture.draw(roomHelperSprite);
            }
            if(map[i][j].roads[0]){
                roadHelperSpriteVertical.setPosition(
                        (float)(j * (32 + 8 * biome.getRoadLengthMax()) + 36),
                        (float)(i * (32 + 8 * biome.getRoadLengthMax()) + 16 - 8 * biome.getRoadLengthMax()));
                this->texture.draw(roadHelperSpriteVertical);
            }
            if(map[i][j].roads[1]){
                roadHelperSpriteHorizontal.setPosition(
                        (float)(j * (32 + 8 * biome.getRoadLengthMax()) + 48),
                        (float)(i * (32 + 8 * biome.getRoadLengthMax()) + 28));
                this->texture.draw(roadHelperSpriteHorizontal);
            }
        }
    }
    this->texture.display();
    this->sprite.setTexture(&this->texture.getTexture());
}

sf::Vector2i Map::extend(const Biome &biome, sf::Vector2i position, int length) {
    std::random_device device;
    std::mt19937 gen(device());
    std::uniform_int_distribution<> random(0,3);
    for(int i = 0; i < length; i++){
        int x = random(gen);
        if((x == 3 && position.y == 0) || map[position.x][position.y].roads[x]) x = 0;
        if((x == 0 && position.x == 0) || map[position.x][position.y].roads[x]) x = 1;
        if((x == 1 && position.y == this->size.y - 1) || map[position.x][position.y].roads[x]) x = 2;
        if((x == 2 && position.x == this->size.x - 1) || map[position.x][position.y].roads[x]) x = 3;
        if((x == 3 && position.y == 0) || map[position.x][position.y].roads[x])
            throw BadMapGeneration("Ran out of space to expand map, " + std::to_string(length - i - 1) + " rooms left to create.\n");
        if(x < 0 || x > 3)
            throw BadMapGeneration("Position index out of range, index = " + std::to_string(x) + ".\n");
        Road* road = new Road(biome);
        map[position.x][position.y].roads[x] = road;
        switch (x) {
            case 0:
                position.x -= 1;
                x = 2;
                break;
            case 1:
                position.y += 1;
                x = 3;
                break;
            case 2:
                position.x += 1;
                x = 0;
                break;
            default:
                position.y -= 1;
                x = 1;
                break;
        }
        if(!map[position.x][position.y].room)
            map[position.x][position.y].room = new Room(biome);
        map[position.x][position.y].roads[x] = road;
    }
    return position;
}

sf::RectangleShape &Map::getSprite(){
    return sprite;
}

Map::~Map() {
    for(int i = 0; i < this->size.y; i++){
        for(int j = 0; j < this->size.x; j++){
            delete this->map[i][j].room;
            delete this->map[i][j].roads[0];
            delete this->map[i][j].roads[1];

        }
        delete[] this->map[i];
    }
    delete[] this->map;
}
