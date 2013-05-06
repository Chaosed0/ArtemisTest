#ifndef __ANGULARVELCOMPONENT_H
#define __ANGULARVELCOMPONENT_H

#include "Component.h"

#include "SFML/System.hpp"

class AngularVelComponent : public artemis::Component {
public:
	float angularVelocity;

    AngularVelComponent(float angularVelocity) {
		this->angularVelocity = angularVelocity;
    }
};

#endif
