
#include "DestroySystem.h"

#include "HealthComponent.h"
#include "TransformableComponent.h"
#include "EntityFactory.h"

DestroySystem::DestroySystem()
{
	addComponentType<HealthComponent>();
	addComponentType<TransformableComponent>();
}

void DestroySystem::initialize()
{
	healthMapper.init(*world);
	transformableMapper.init(*world);
}

void DestroySystem::processEntity(artemis::Entity &e)
{
	if(healthMapper.get(e)->health <= 0.0f) {
		world->deleteEntity(e);
		EntityFactory::CreateExplosion(*world,
			transformableMapper.get(e)->transformable->getPosition());
	}
}