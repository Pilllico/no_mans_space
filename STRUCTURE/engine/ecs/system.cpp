#include "system.h"

System::System()
{

}

void System::update(bitmap signature, Entity e)
{
    // Entity e has new signature

    if (signature != systemSignature)
        entityList.erase(find(entityList.begin(), entityList.end(), e));

}

System::~System()
{

}
