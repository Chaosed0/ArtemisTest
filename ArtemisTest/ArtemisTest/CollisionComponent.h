
#ifndef __COLLISIONCOMPONENT_H
#define __COLLISIONCOMPONENT_H

#include "Entity.h"

#include <SFML/System.hpp>

class CollisionComponent : public artemis::Component
{
public:
	sf::FloatRect collisionRect;
	bool isCollidable;
	CollisionComponent(sf::FloatRect collisionRect, bool isCollidable)
	{
		this->collisionRect = collisionRect;
		this->isCollidable = isCollidable;
	}
};

#endif