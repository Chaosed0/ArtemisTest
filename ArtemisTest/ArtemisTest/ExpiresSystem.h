
#ifndef __EXPIRESSYSTEM_H
#define __EXPIRESSYSTEM_H

#include "EntityProcessingSystem.h"
#include "ComponentMapper.h"

class ExpiresComponent;

class ExpiresSystem : public artemis::EntityProcessingSystem
{
private:
	artemis::ComponentMapper<ExpiresComponent> expiresMapper;

public:
	ExpiresSystem();

	virtual void initialize();

	virtual void processEntity(artemis::Entity &e);
};

#endif