
#ifndef __MOVEMENTSYSTEM_H
#define __MOVEMENTSYSTEM_H

#include "EntityProcessingSystem.h"
#include "ComponentMapper.h"

class VelocityComponent;
class TransformableComponent;

class MovementSystem : public artemis::EntityProcessingSystem {
private:
    artemis::ComponentMapper<VelocityComponent> velocityMapper;
    artemis::ComponentMapper<TransformableComponent> transformableMapper;

public:
    MovementSystem();

    virtual void initialize();

    virtual void processEntity(artemis::Entity &e);
};

#endif