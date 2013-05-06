
#ifndef __COLLISIONCOMPONENT_H
#define __COLLISIONCOMPONENT_H

#include "Entity.h"

#include <SFML/System.hpp>

class CollisionComponent : public artemis::Component
{
public:
	sf::FloatRect collisionRect;
	CollisionComponent(sf::FloatRect collisionRect)
	{
		this->collisionRect = collisionRect;
	}
};

#endif