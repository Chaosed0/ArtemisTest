
#include "AnimSystem.h"

#include "AnimationComponent.h"
#include "RenderComponent.h"
#include "AnimManager.h"

AnimSystem::AnimSystem()
{
	addComponentType<AnimationComponent>();
	addComponentType<RenderComponent>();
}

void AnimSystem::initialize()
{
	animMapper.init(*world);
	renderMapper.init(*world);
}

void AnimSystem::processEntity(artemis::Entity &e)
{
	AnimationComponent* animComponent = animMapper.get(e);
	sf::Sprite* sprite = ((sf::Sprite*)renderMapper.get(e)->drawable.get());

	animComponent->frameTimer -= sf::seconds(world->getDelta());
	AnimManager::PlayAnim(*animComponent);

	unsigned int textureXLim = sprite->getTexture()->getSize().x / animComponent->animRectSize.x;
	sf::Vector2i textureCoord(animComponent->curFrame % textureXLim*animComponent->animRectSize.x,
		animComponent->curFrame / textureXLim*animComponent->animRectSize.y);
	sf::IntRect textureRect(textureCoord, animComponent->animRectSize);
	sprite->setTextureRect(textureRect);
}