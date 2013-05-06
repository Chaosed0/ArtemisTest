
#include "RenderBoxSystem.h"
#include "CollisionComponent.h"
#include "TransformableComponent.h"
#include "SATCollision.h"

RenderBoxSystem::RenderBoxSystem(sf::RenderWindow& window) :
	window(window)
{
	addComponentType<CollisionComponent>();
	addComponentType<TransformableComponent>();
};

void RenderBoxSystem::initialize()
{
	collisionMapper.init(*world);
	transformableMapper.init(*world);
};

void RenderBoxSystem::processEntity(artemis::Entity &e)
{
	sf::CircleShape circle(5.0f);
	circle.setOrigin(circle.getRadius()/2.0f, circle.getRadius()/2.0f);
	circle.setFillColor(sf::Color(0,255,0));
	std::vector<sf::Vector2f> points = SATCollision::GetTransformedRect(
		*transformableMapper.get(e)->transformable, collisionMapper.get(e)->collisionRect);
	for(unsigned int i = 0; i < points.size(); i++) {
		circle.setPosition(points[i]);
		window.draw(circle);
	}
};