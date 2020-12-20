#include "entitymanager.h"

EntityManager * EntityManager::getInstance() {
    if (EntityManager::instance == nullptr) {
        EntityManager::instance = new EntityManager();
    }

    return EntityManager::instance;
}

Entity EntityManager::createEntity() {

    Entity E = Entity();

    entitiesList.insert(std::make_pair(E, std::bitset<16>()));

    return E;
}

void EntityManager::addComponentToEntity(Component* component, Entity e) {

    // Récupère le bitset du composant
    std::bitset<16> bitset = component->getBitset();

    // Ajoute à l'entité
    entitiesList.at(e) = entitiesList.at(e) |= bitset;

    // Cherche la position du bit de ce type de composant
    unsigned short pos = 0;
    for (unsigned short i = 0; i < 16; ++i) {
        if (bitset.test(i)) {
            pos = i;
            break;
        }
    }

    ComponentManager* test = componentManagers[pos];

    test->addComponent(e, component);
}

void EntityManager::addComponentsToEntity(std::vector<Component*> components, Entity e) {

    for (Component* c : components) {
        addComponentToEntity(c, e);
    }

}

std::bitset<16> EntityManager::getBitMapFromEntity(Entity e) {
    return entitiesList[e];
}

std::vector<Component*> getComponentsFromEntity(std::bitset<16> bitset, Entity e) {

    std::vector<Component*> out;

    for (int i = 0; bitset.size(); ++i) {
        if (bitset.test(i)) {



        }
    }

}
