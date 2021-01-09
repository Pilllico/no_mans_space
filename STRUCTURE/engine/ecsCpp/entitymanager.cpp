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
    componentManagers.insert(std::make_pair(Physics::componentSignature, new PhysicsManager()));
	componentManagers.insert(std::make_pair(Render::componentSignature, new RenderManager()));
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

void EntityManager::addComponentToEntity(Entity e, Component* component) {

    // Récupère le bitmap du composant
    bitmap signature = component->getBitMap();

    //std::cout << "Bitmap du composant a ajouter " << signature << std::endl;
    //std::cout << "Avant : " << entitiesList.at(e) << std::endl;

    // Ajoute à l'entité
    entitiesList.at(e) = entitiesList.at(e) |= signature;

    //std::cout << "Apres : " << entitiesList.at(e) << std::endl;

    componentManagers.at(signature)->addComponent(e, component);

    notifyAll(e);
}

void EntityManager::addComponentToEntity(Entity e, btVector3 pos, btVector3 rot, btVector3 s)
{
    Transform transform(pos, rot, s);
    this->addComponentToEntity(e, &transform);
}

void EntityManager::addComponentToEntity(Entity e, float m, CollisionShape cs)
{
    Physics p(m, cs);
    this->addComponentToEntity(e, &p);
}

void EntityManager::addComponentToEntity(Entity e, GLuint programID, std::string object_name)
{
	Render r;
	r.programID = programID;
	r.object_name = object_name;

	this->addComponentToEntity(e, &r);
}

void EntityManager::addComponentsToEntity(Entity e, std::vector<Component*> components) {

    for (Component* c : components) {
        addComponentToEntity(e, c);
    }
}

bitmap EntityManager::getBitMapFromEntity(Entity e) {
    return entitiesList[e];
}

ComponentManager* EntityManager::getComponentManagerForSystem(bitmap signature) {
    if (signature.any())
    {
        for (auto it = componentManagers.begin(); it != componentManagers.end(); it++)
        {
            if (it->first == signature)
                return it->second;
        }
    }
    return nullptr;
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

        notifyAll(e);

        return true;
    }
    else
        return false;
}

void EntityManager::registerSystem(System * system)
{
    systemList.insert(system);
}

void EntityManager::notifyAll(Entity e)
{
    for (System* s : systemList)
        s->update(e);
}
