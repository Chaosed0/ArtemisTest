
#ifndef __ANIMSYSTEM_H
#define __ANIMSYSTEM_H

#include "EntityProcessingSystem.h"
#include "ComponentMapper.h"

class AnimationComponent;
class RenderComponent;

class AnimSystem : public artemis::EntityProcessingSystem
{
private:
	artemis::ComponentMapper<AnimationComponent> animMapper;
	artemis::ComponentMapper<RenderComponent> renderMapper;

public:
	AnimSystem();

	virtual void initialize();

	virtual void processEntity(artemis::Entity &e);
};

#endif