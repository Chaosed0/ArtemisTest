
#include "MovementSystem.h"

#include "TransformableComponent.h"
#include "VelocityComponent.h"

MovementSystem::MovementSystem() {
	addComponentType<VelocityComponent>();
	addComponentType<TransformableComponent>();
};

void MovementSystem::initialize() {
	velocityMapper.init(*world);
	transformableMapper.init(*world);
};

void MovementSystem::processEntity(artemis::Entity &e) {
	sf::Vector2f entityPos = transformableMapper.get(e)->transformable->getPosition();
	sf::Vector2f entityVel = velocityMapper.get(e)->velocity;
	transformableMapper.get(e)->transformable->setPosition(entityPos + entityVel*world->getDelta());
};