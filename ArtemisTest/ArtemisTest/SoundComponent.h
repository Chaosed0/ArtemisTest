
#ifndef __SOUNDCOMPONENT_H
#define __SOUNDCOMPONENT_H

#include "Component.h"

#include <memory>

#include "SoundManager.h"

#include "SFML/Audio.hpp"

//This is just here so the player input system processes only the player
class SoundComponent : public artemis::Component
{
public:
	std::unique_ptr<sf::Sound> sound;

	SoundComponent() {
	}

	static SoundManager soundManager;
};

SoundManager SoundComponent::soundManager;

#endif