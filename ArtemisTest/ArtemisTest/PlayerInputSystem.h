
#ifndef __PLAYERINPUTSYSTEM_H
#define __PLAYERINPUTSYSTEM_H

#include "EntityProcessingSystem.h"
#include "ComponentMapper.h"

class VelocityComponent;
class TransformableComponent;
class PlayerComponent;

#include "SFML/Window.hpp"

#include <cmath>
#include <vector>

class PlayerInputSystem : public artemis::EntityProcessingSystem {
private:
    artemis::ComponentMapper<VelocityComponent> velocityMapper;
	artemis::ComponentMapper<TransformableComponent> TransformableMapper;
	artemis::ComponentMapper<PlayerComponent> playerMapper;

	sf::Vector2i mousePt;
	std::vector<bool> keyDown;
	std::vector<bool> mouseDown;

	bool shootingBeam;
	sf::Time beamTime;
public:
    PlayerInputSystem();

    virtual void initialize();

    virtual void processEntity(artemis::Entity &e);

	void SetMouse(sf::Vector2i mouse);

	void KeyDown(sf::Keyboard::Key key);

	void KeyRelease(sf::Keyboard::Key key);

	void MousePress(sf::Mouse::Button button);

	void MouseRelease(sf::Mouse::Button button);

	const static float playerMoveSpeed;
	const static float playerSlowMoveSpeed;
	const static sf::Time powerDownTime;
};

#endif