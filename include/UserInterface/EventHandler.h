#ifndef OOP_EVENTHANDLER_H
#define OOP_EVENTHANDLER_H


#include <SFML/Window/Event.hpp>

class EventHandler {
public:

    /// event handler send events to this so that they will be processed
    /// @return true if the event was used in any way
    virtual bool handleEvent(const sf::Event& event) = 0;
};


#endif //OOP_EVENTHANDLER_H
