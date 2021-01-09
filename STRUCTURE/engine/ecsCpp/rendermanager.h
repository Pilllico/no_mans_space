#pragma once

#include <unordered_map>
#include "entity.h"
#include "Render.h"
#include "componentmanager.h"

class RenderManager : public ComponentManager
{
public:
	RenderManager();
	virtual void addComponent(Entity e, Component* component);
	virtual void deleteComponent(Entity e);
	Render& getRender(Entity e);
	std::unordered_map<Entity, Render, EntityHasher>& getAllRenders();
	~RenderManager();
private:
	//std::vector<Transform> data;
	std::unordered_map<Entity, Render, EntityHasher> data;
};

