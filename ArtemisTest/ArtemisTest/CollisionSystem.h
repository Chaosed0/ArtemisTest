
#ifndef __COLLISIONSYSTEM_H
#define __COLLISIONSYSTEM_H

#include <vector>
#include <memory>

#include "EntityProcessingSystem.h"
#include "ComponentMapper.h"

class TransformableComponent;
class CollisionComponent;

class CollisionSystem : public artemis::EntitySystem {
private:
    artemis::ComponentMapper<TransformableComponent> transformableMapper;
    artemis::ComponentMapper<CollisionComponent> collisionMapper;

public:
    CollisionSystem();

    virtual void initialize();

	virtual void processEntities(artemis::ImmutableBag<artemis::Entity*> & entities);
	virtual bool checkProcessing();
private:
	class CollisionHandler;
	class CollisionGroup;
	std::vector<CollisionGroup> collisionGroups;
};


class CollisionSystem::CollisionHandler
{
public:
	CollisionHandler(artemis::World* world);
	virtual void HandleCollision(artemis::Entity* a, artemis::Entity* b) = 0;
protected:
	artemis::World* world;
};


class CollisionSystem::CollisionGroup
{
public:
	CollisionGroup(artemis::ImmutableBag<artemis::Entity*>* entityGroup1,
		artemis::ImmutableBag<artemis::Entity*>* entityGroup2, CollisionHandler* handler);

	CollisionGroup(CollisionGroup&& other)
		: handler(std::move(other.handler))
	{
		entityGroup1 = other.entityGroup1;
		entityGroup2 = other.entityGroup2;
	}

	void CheckForCollisions();
private:
	bool CollisionExists(artemis::Entity* entity1, artemis::Entity* entity2);

	artemis::ImmutableBag<artemis::Entity*>* entityGroup1;
	artemis::ImmutableBag<artemis::Entity*>* entityGroup2;
	std::unique_ptr<CollisionHandler> handler;
};

#endif