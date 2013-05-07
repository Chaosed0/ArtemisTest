
#include "ExpiresSystem.h"

#include "ExpiresComponent.h"

ExpiresSystem::ExpiresSystem()
{
	addComponentType<ExpiresComponent>();
}

void ExpiresSystem::initialize()
{
	expiresMapper.init(*world);
}

void ExpiresSystem::processEntity(artemis::Entity &e)
{
	expiresMapper.get(e)->timer += sf::seconds(world->getDelta());
	if(expiresMapper.get(e)->timer > expiresMapper.get(e)->expiry) {
		world->deleteEntity(e);
	}
}