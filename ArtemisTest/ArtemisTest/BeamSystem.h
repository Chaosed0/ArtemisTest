
#ifndef __BEAMSYSTEM_H
#define __BEAMSYSTEM_H

#include "EntityProcessingSystem.h"
#include "ComponentMapper.h"

class BeamComponent;
class AngularVelComponent;
class CollisionComponent;

#include "SFML/System.hpp"

#include <cmath>

class BeamSystem : public artemis::EntityProcessingSystem {
private:
    artemis::ComponentMapper<BeamComponent> beamMapper;
	artemis::ComponentMapper<AngularVelComponent> angularVelMapper;
	artemis::ComponentMapper<CollisionComponent> collisionMapper;

	sf::Vector2i mousePos;

public:
    BeamSystem();

    virtual void initialize();

    virtual void processEntity(artemis::Entity &e);

	float XFunction(float beamHeight, sf::Time time);

	float YFunction(float beamWidth, sf::Time time);

	void SetMouse(sf::Vector2i mousePos);

	const static sf::Time windupTime;
	const static sf::Time sustainTime;
	const static float angularVelocity;
};

#endif