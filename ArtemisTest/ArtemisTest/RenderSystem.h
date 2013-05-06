
#ifndef __RENDERSYSTEM_H
#define __RENDERSYSTEM_H

#include "EntityProcessingSystem.h"
#include "ComponentMapper.h"

class RenderComponent;

#include "SFML/Graphics.hpp"

class RenderSystem : public artemis::EntityProcessingSystem {
private:
    artemis::ComponentMapper<RenderComponent> RenderMapper;
	sf::RenderWindow& window;

public:
    RenderSystem(sf::RenderWindow& window);

    virtual void initialize();

    virtual void processEntity(artemis::Entity &e);
};

#endif