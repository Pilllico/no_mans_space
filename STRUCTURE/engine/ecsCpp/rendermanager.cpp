#include "RenderManager.h"

RenderManager::RenderManager()
{
}

void RenderManager::addComponent(Entity e, Component * component)
{
	data.insert(std::make_pair(e, *dynamic_cast<Render*>(component)));
}

void RenderManager::deleteComponent(Entity e)
{
	data.erase(e);
}

Render & RenderManager::getRender(Entity e)
{
	return data.at(e);
}

std::unordered_map<Entity, Render, EntityHasher>& RenderManager::getAllRenders()
{
	return data;
}

RenderManager::~RenderManager()
{
}
