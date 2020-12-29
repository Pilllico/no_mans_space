#include "displaysystem.h"

#include <iostream>

displaySystem::displaySystem()
{
    time = std::clock();
    systemSignature = bitmap("00000001");
}

std::ostream& operator<< (std::ostream& os, const QVector3D& v)
{
    os << v.x() << " " << v.y() << " " << v.z();
    return os;
}

void displaySystem::execute()
{
    std::clock_t t1 = clock();
    if ((t1 - time) / (double) CLOCKS_PER_SEC > 2.0) {
        time = t1;
        std::cout << "Test" << std::endl;

        std::cout << entityList.size() << std::endl;

        for (auto it = entityList.begin(); it !=entityList.end(); it++)
        {
            std::cout << "id: " << it->id << std::endl;
            bitmap signature = entityManager.getBitMapFromEntity(*it);
            std::cout << "Signature: " << signature << std::endl;

            std::vector<ComponentManager*> componentManagers = entityManager.getComponentManagersForSystem(systemSignature);

            Transform transform = dynamic_cast<TransformManager*>(componentManagers.at(0))->getTransform(*it);

            std::cout << transform.getPosition() << std::endl;
        }
    }
}
