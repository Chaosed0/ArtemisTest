
#ifndef __TRANSFORMABLECOMPONENT_H
#define __TRANSFORMABLECOMPONENT_H

#include "Component.h"

#include "SFML/Graphics.hpp"

#include <memory>

class TransformableComponent : public artemis::Component
{
public:
	std::shared_ptr<sf::Transformable> transformable;
    TransformableComponent(std::shared_ptr<sf::Transformable> transformable)
    {
		this->transformable = transformable;
    }
};

#endif