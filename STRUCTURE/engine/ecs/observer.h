#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>
#include "subject.h"

class Observer
{
public:
    Observer();
    virtual void update() = 0;
    virtual ~Observer();
private:
    std::vector<Subject*> subjects;
};

#endif // OBSERVER_H
