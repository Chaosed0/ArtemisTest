
#ifndef __HEALTHCOMPONENT_H
#define __HEALTHCOMPONENT_H

#include "Component.h"

class HealthComponent : public artemis::Component
{
public:
	float health;
	HealthComponent(float health)
	{
		this->health = health;
	}
};

#endif