#include "entitymanager.h"
#include <iostream>

#include "system.h"

EntityManager & EntityManager::getInstance() {
    static EntityManager instance;
    return instance;
}

EntityManager::EntityManager()
{
    componentManagers.insert(std::make_pair(Transform::componentSignature, new TransformManager()));
}

EntityManager::~EntityManager()
{
    for (auto it = componentManagers.begin(); it != componentManagers.end(); it++)
    {
        delete it->second;
    }
    std::cout << "~EntityManager()" << std::endl;
}

Entity EntityManager::createEntity() {

    Entity E = Entity();

    entitiesList.insert(std::make_pair(E, bitmap()));

    return E;
}

void EntityManager::addComponentToEntity(Component* component, Entity e) {

    // Récupère le bitmap du composant
    bitmap signature = component->getBitMap();

    // Ajoute à l'entité
    entitiesList.at(e) = entitiesList.at(e) |= signature;

    componentManagers.at(signature)->addComponent(e, component);

    notifyAll(signature, e);
}

void EntityManager::addComponentsToEntity(std::vector<Component*> components, Entity e) {

    for (Component* c : components) {
        addComponentToEntity(c, e);
    }
}

bitmap EntityManager::getBitMapFromEntity(Entity e) {
    return entitiesList[e];
}

std::vector<ComponentManager*> EntityManager::getComponentManagersForSystem(bitmap signature) {

    std::vector<ComponentManager*> out;

    for (size_t i = 0; i < signature.size(); ++i) {
        if (signature.test(i)) {

            bitmap mask;
            mask.set(i);

            for (auto it = componentManagers.begin(); it != componentManagers.end(); it++)
            {
                if (it->first == mask)
                    out.push_back(it->second);
            }
        }
    }
    return out;
}

bool EntityManager::deleteEntity(Entity e) {

    // Update component
    // Delete all components of this entity
    deleteComponentsFromEntity(entitiesList.at(e), e);

    if (entitiesList.erase(e) == 1)
        return true;
    else
        return false;
}

bool EntityManager::deleteComponentsFromEntity(bitmap signature, Entity e) {
    if ((entitiesList.at(e) & signature).any()) {
        // Essaye d'enlever un component présent

        if ((entitiesList.at(e) & signature) != signature)
            std::cerr << "Bitmap mal écrit!" << std::endl;

        entitiesList.at(e) &= ~(signature);

        for (unsigned short i = 0; i < signature.size(); ++i) {
            if (signature.test(i)) {

                bitmap mask;
                mask.set(i);

                for (auto it = componentManagers.begin(); it != componentManagers.end(); it++)
                {
                    if (it->first == mask)
                        it->second->deleteComponent(e);
                }
            }
        }

        notifyAll(signature, e);

        return true;
    }
    else
        return false;
}

void EntityManager::registerSystem(System * system)
{
    systemList.insert(system);
}

void EntityManager::notifyAll(bitmap signature, Entity e)
{
    for (System* s : systemList)
        s->update(signature, e);
}
