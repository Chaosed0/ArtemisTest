
#ifndef __ANGULARSYSTEM_H
#define __ANGULARSYSTEM_H

#include "EntityProcessingSystem.h"
#include "ComponentMapper.h"

class AngularVelComponent;
class TransformableComponent;

class AngularSystem : public artemis::EntityProcessingSystem {
private:
    artemis::ComponentMapper<AngularVelComponent> velocityMapper;
    artemis::ComponentMapper<TransformableComponent> transformableMapper;

public:
    AngularSystem();

    virtual void initialize();

    virtual void processEntity(artemis::Entity &e);
};

#endif