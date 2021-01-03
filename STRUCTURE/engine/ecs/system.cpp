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
    //std::cout << "System Signature : " << systemSignature << std::endl;
    //std::cout << "Entity Signature : " << signature << std::endl;

    if (find(entityList.begin(), entityList.end(), e) != entityList.end()) {
        //std::cout << "Entity found in system" << std::endl;
        if ((signature&systemSignature) != systemSignature) {
            //std::cout << (signature&systemSignature) << std::endl;
            entityList.erase(find(entityList.begin(), entityList.end(), e));
            //std::cout << "Entity remove form system" << std::endl;
        }
    }
    else {
        //std::cout << "Entity not found in system" << std::endl;
        //std::cout << (signature&systemSignature) << std::endl;
        if ((signature&systemSignature) == systemSignature) {
            entityList.push_back(e);
            //std::cout <<"Entity added to system" << std::endl;
        }
    }
}

System::~System()
{

}
