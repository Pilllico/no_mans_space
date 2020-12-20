#ifndef COMPONENT_H
#define COMPONENT_H

#include <bitset>

struct Component
{
public:
    virtual std::bitset<16> getBitset() = 0;
    virtual ~Component();
protected:
    std::bitset<16> id;
};

#endif // COMPONENT_H
