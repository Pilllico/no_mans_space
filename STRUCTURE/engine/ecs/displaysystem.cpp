#include "displaysystem.h"

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

bool displaySystem::execute()
{
    std::clock_t t1 = clock();
    if ((t1 - time) / static_cast<double>(CLOCKS_PER_SEC) > 2.0) {
        time = t1;
        std::cout << "Test" << std::endl;

        std::cout << entityList.size() << std::endl;

        for (auto it = entityList.begin(); it !=entityList.end(); it++)
        {
            std::cout << "id: " << it->id << std::endl;
            bitmap signature = entityManager.getBitMapFromEntity(*it);
            std::cout << "Signature: " << signature << std::endl;

            TransformManager* transformManager = dynamic_cast<TransformManager*>(EntityManager::getInstance().getComponentManagerForSystem(bitmap("1")));
            Transform transform = transformManager->getTransform(*it);

            std::cout << transform.position << std::endl;
        }
        std::cout << "End display System" << std::endl;
        return true;
    }
    return false;
}
