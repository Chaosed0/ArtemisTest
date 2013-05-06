
#include "AngularSystem.h"
#include "TransformableComponent.h"
#include "AngularVelComponent.h"
#include "Utility.h"

AngularSystem::AngularSystem() {
	addComponentType<AngularVelComponent>();
	addComponentType<TransformableComponent>();
};

void AngularSystem::initialize() {
	velocityMapper.init(*world);
	transformableMapper.init(*world);
};

void AngularSystem::processEntity(artemis::Entity &e) {
	float rotation = transformableMapper.get(e)->transformable->getRotation()*TO_RAD;
	float angularVel = velocityMapper.get(e)->angularVelocity;
	transformableMapper.get(e)->transformable->setRotation(
		TO_DEG*shiftAngle(rotation+angularVel*world->getDelta()));
};