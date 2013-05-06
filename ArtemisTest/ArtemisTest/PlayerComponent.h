
#ifndef __PLAYERCOMPONENT_H
#define __PLAYERCOMPONENT_H

#include "Component.h"

#include "SFML/System.hpp"

//This is just here so the player input system processes only the player
class PlayerComponent : public artemis::Component
{
public:
	sf::Keyboard::Key upKey;
	sf::Keyboard::Key downKey;
	sf::Keyboard::Key leftKey;
	sf::Keyboard::Key rightKey;

	sf::Mouse::Button shootButton;
	PlayerComponent(sf::Keyboard::Key upKey, sf::Keyboard::Key downKey,
			sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey,
			sf::Mouse::Button shootButton) {
		this->upKey = upKey;
		this->downKey = downKey;
		this->leftKey = leftKey;
		this->rightKey = rightKey;
		this->shootButton = shootButton;
	}
};

#endif