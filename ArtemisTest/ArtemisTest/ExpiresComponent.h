
#ifndef	__EXPIRESCOMPONENT_H
#define __EXPIRESCOMPONENT_H

#include "Component.h"

#include <SFML/System.hpp>

class ExpiresComponent : public artemis::Component
{
public:
	sf::Time timer;
	sf::Time expiry;
	ExpiresComponent(sf::Time expiry)
	{
		timer = sf::Time::Zero;
		this->expiry = expiry;
	}
};

#endif