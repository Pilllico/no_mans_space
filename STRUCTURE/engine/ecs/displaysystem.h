#ifndef DISPLAYSYSTEM_H
#define DISPLAYSYSTEM_H

#include "system.h"
#include <ctime>

class displaySystem : public System
{
public:
    displaySystem();
    void virtual execute();
private:
    std::clock_t time;
};

#endif // DISPLAYSYSTEM_H
