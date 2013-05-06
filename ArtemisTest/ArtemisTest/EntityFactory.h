
#ifndef __ENTITYFACTORY_H
#define __ENTITYFACTORY_H

#include "World.h"
#include "Entity.h"

#include "TextureManager.h"

class EntityFactory
{
public:
	static artemis::Entity& CreatePlayer(artemis::World& world, const sf::Vector2f& pos);

	static artemis::Entity& EntityFactory::CreateBeam(artemis::World& world, const sf::Vector2f& pos,
										   const sf::Vector2i& pointPos);

	static artemis::Entity& CreateStaticTest(artemis::World& world, const sf::Vector2f& pos);
private:
};

#endif