#ifndef OOP_ANIMATION_H
#define OOP_ANIMATION_H

#include "Drawn.h"

template<class T>
class Animation : public Drawn{
private:
    T* sprite;
    std::vector<sf::Vector2i> moves;
    std::vector<sf::Vector2f> scale;
    int step{};
    int delay{};
protected:

    void addPos(float x, float y) override;
public:

    /// default constructor creates an animation
    /// @param length length of animation in frames
    /// @param step first time starting frame if this is a negative value the animation will not be played until reset
    /// @param delay amount of frames each animation frame will be played for
    explicit Animation(int step = 0, int length = 1, int delay = 1);

    virtual ~Animation();

    T& getSprite();

    /// sets the animation frames scaling each frame the scale will be set to the according value
    void setScale(const std::vector<sf::Vector2f> &vector);

    /// sets the animation frames moves each game the sprite will move according to the value
    void setMoves(const std::vector<sf::Vector2i> &vector);

    void draw(sf::RenderWindow& window) override;

    void reset();
};

template<class T>
void Animation<T>::reset() {
    this->step = 0;
}

template<class T>
void Animation<T>::setMoves(const std::vector<sf::Vector2i> &vector){
    Animation::moves = vector;
}

template<class T>
void Animation<T>::setScale(const std::vector<sf::Vector2f> &vector) {
    Animation::scale = vector;
}

template<class T>
Animation<T>::~Animation() {
    delete this->sprite;
}

template<class T>
T &Animation<T>::getSprite() {
    return *(this->sprite);
}

template<class T>
Animation<T>::Animation(int step, int length, int delay) {
    if(delay <= 0) delay = 1;
    this->sprite = new T;
    if(step < length)
        this->step = step;
    else
        this->step = -1;
    if(length <= 0)
        length = 1;
    this->moves = std::vector<sf::Vector2i>(length,{0,0});
    this->scale = std::vector<sf::Vector2f>(length,{1,1});
    this->delay = delay;
}

template<class T>
void Animation<T>::draw(sf::RenderWindow &window) {
    if(this->step == (int)this->moves.size() * this->delay)
        this->step = -1;
    if(this->step >= 0){
        if(this->step % this->delay == 0){
            this->addPosition<sf::Vector2i>(this->moves[step / this->delay]);
            this->sprite->setScale(this->scale[step / this->delay]);
        }
        this->step++;
    }
    window.draw(*(this->sprite));
}

template<class T>
void Animation<T>::addPos(float x, float y) {
    this->sprite->setPosition(this->sprite->getPosition() + sf::Vector2f(x,y));
}

#endif //OOP_ANIMATION_H
