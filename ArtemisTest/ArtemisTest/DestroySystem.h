
#ifndef __DESTROYSYSTEM_H
#define __DESTROYSYSTEM_H

#include "EntityProcessingSystem.h"
#include "ComponentMapper.h"

class HealthComponent;
class TransformableComponent;

class DestroySystem : public artemis::EntityProcessingSystem
{
private:
    artemis::ComponentMapper<HealthComponent> healthMapper;
	artemis::ComponentMapper<TransformableComponent> transformableMapper;

public:
    DestroySystem();

    virtual void initialize();

    virtual void processEntity(artemis::Entity &e);
private:
};

#endif