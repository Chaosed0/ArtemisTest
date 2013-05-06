#ifndef __VELOCITYCOMPONENT_H
#define __VELOCITYCOMPONENT_H

#include "Component.h"

#include "SFML/System.hpp"

class VelocityComponent : public artemis::Component {
public:
	sf::Vector2f velocity;

    VelocityComponent(float velocityX, float velocityY)
    {
		velocity.x = velocityX;
		velocity.y = velocityY;
    }
	VelocityComponent(sf::Vector2f velocity)
	{
		this->velocity = velocity;
	}
};

#endif
