
#ifndef __BEAMCOMPONENT_H 
#define __BEAMCOMPONENT_H 

#include "Component.h"

#include "RenderComponent.h"

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class BeamComponent : public artemis::Component
{
public:
	sf::Time timer;
	bool isFired;
	bool hasPlayedSound;
	sf::Vector2f beamSize;
	std::shared_ptr<sf::RectangleShape> rect;
	std::shared_ptr<sf::Sound> curSound;
	BeamComponent(std::shared_ptr<sf::RectangleShape> rect, sf::Vector2f beamSize) {
		timer = sf::Time::Zero;
		isFired = false;
		hasPlayedSound = false;
		this->beamSize = beamSize;
		this->rect = rect;
	}
};

#endif