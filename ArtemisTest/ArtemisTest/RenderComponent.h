
#ifndef __RENDERCOMPONENT_H
#define __RENDERCOMPONENT_H

#include "Component.h"

#include "SFML/Graphics.hpp"

#include <memory>

class RenderComponent : public artemis::Component 
{
public:
	std::shared_ptr<sf::Drawable> drawable;
	RenderComponent(std::shared_ptr<sf::Drawable> drawable)
	{
		this->drawable = drawable;
	}
};

#endif