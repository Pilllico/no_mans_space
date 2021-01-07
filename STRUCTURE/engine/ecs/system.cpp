#include "system.h"
#include <iostream>

System::System()
{
    EntityManager::getInstance().registerSystem(this);
}

void System::update(Entity e)
{
    // Entity e has new signature
    bitmap signature = EntityManager::getInstance().getBitMapFromEntity(e);

    std::cout << "System " << systemSignature << " notified" << std::endl;

    if (find(entityList.begin(), entityList.end(), e) != entityList.end()) {
        if ((signature&systemSignature) != systemSignature) {        
            entityList.erase(find(entityList.begin(), entityList.end(), e));
        }
    }
    else {
        if ((signature&systemSignature) == systemSignature) {
            entityList.push_back(e);
        }
    }
}

System::~System()
{

}
