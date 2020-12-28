#include "entitymanager.h"
#include <iostream>

EntityManager & EntityManager::getInstance() {
    /*if (EntityManager::instance == nullptr) {
        EntityManager::instance = new EntityManager();
    }

    return EntityManager::instance;*/
    static EntityManager instance;
    return instance;
}

EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{

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

    // Cherche la position du bit de ce type de composant
    unsigned short pos = 0;
    for (unsigned short i = 0; i < signature.size(); ++i) {
        if (signature.test(i)) {
            pos = i;
            break;
        }
    }

   componentManagers[pos]->addComponent(e, component);
}

void EntityManager::addComponentsToEntity(std::vector<Component*> components, Entity e) {

    for (Component* c : components) {
        addComponentToEntity(c, e);
    }

}

std::bitset<16> EntityManager::getBitMapFromEntity(Entity e) {
    return entitiesList[e];
}

std::vector<ComponentManager*> EntityManager::getComponentManagersForSystem(bitmap signature) {

    std::vector<ComponentManager*> out;

    for (int i = 0; signature.size(); ++i) {
        if (signature.test(i)) {

            bitmap mask;
            mask.set(i);

            for (ComponentManager* cm : componentManagers)
            {
                if (cm->id == mask)
                    out.push_back(cm);
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

                for (ComponentManager* cm : componentManagers)
                {
                    if (cm->id == mask) {
                        cm->deleteComponent(e);
                    }
                }
            }
        }

        notifyAll(signature, e);

        return true;
    }
    else
        return false;
}

void EntityManager::notifyAll(bitmap signature, Entity e)
{
    for (System* s : systemList) {}
        //s->update(bitmap signature, Entity e);
}
