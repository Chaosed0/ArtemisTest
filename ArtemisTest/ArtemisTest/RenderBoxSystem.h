
#ifndef __RENDERBOXSYSTEM_H
#define __RENDERBOXSYSTEM_H

#include "EntityProcessingSystem.h"
#include "ComponentMapper.h"

class CollisionComponent;
class TransformableComponent;

#include "SFML/Graphics.hpp"

class RenderBoxSystem : public artemis::EntityProcessingSystem {
private:
    artemis::ComponentMapper<CollisionComponent> collisionMapper;
	artemis::ComponentMapper<TransformableComponent> transformableMapper;
	sf::RenderWindow& window;

public:
    RenderBoxSystem(sf::RenderWindow& window);

    virtual void initialize();

    virtual void processEntity(artemis::Entity &e);
};

#endif