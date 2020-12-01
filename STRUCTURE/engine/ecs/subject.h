#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>

class Observer;

class Subject
{
public:
    Subject();
    virtual void notifyObserver() = 0;
    virtual void registerObserver(Observer* observer);
    virtual void unregisterObserver(Observer* observer);
    virtual ~Subject();
private:
    std::vector<Observer*> observer;
};

#endif // SUBJECT_H
