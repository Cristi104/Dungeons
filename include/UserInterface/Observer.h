#ifndef OOP_OBSERVER_H
#define OOP_OBSERVER_H

template<class T>
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(T& param) = 0;
};

#endif //OOP_OBSERVER_H
