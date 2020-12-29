#include "system.h"
#include <iostream>

System::System()
{
    EntityManager::getInstance().registerSystem(this);
}

void System::update(bitmap signature, Entity e)
{
    // Entity e has new signature

    std::cout << "Notified" << std::endl;

    if (find(entityList.begin(), entityList.end(), e) != entityList.end()) {
        if ((signature&systemSignature) != systemSignature)
            entityList.erase(find(entityList.begin(), entityList.end(), e));
    }
    else {

    if ((signature&systemSignature) == systemSignature)
        entityList.push_back(e);

    }
}

System::~System()
{

}
