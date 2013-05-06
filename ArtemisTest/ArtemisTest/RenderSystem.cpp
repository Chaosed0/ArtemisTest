
#include "RenderSystem.h"
#include "RenderComponent.h"

RenderSystem::RenderSystem(sf::RenderWindow& window) :
	window(window)
{
	addComponentType<RenderComponent>();
};

void RenderSystem::initialize()
{
	RenderMapper.init(*world);
};

void RenderSystem::processEntity(artemis::Entity &e)
{
	window.draw(*RenderMapper.get(e)->drawable);
};