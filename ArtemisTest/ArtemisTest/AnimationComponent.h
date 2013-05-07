
#ifndef __ANIMATIONCOMPONENT_H
#define __ANIMATIONCOMPONENT_H

#include "Component.h"

#include <map>
#include <vector>
#include <SFML/System.hpp>

#include "AnimManager.h"


class AnimationComponent : public artemis::Component
{
public:
	sf::Vector2i animRectSize;
	int curAnim;
	int curFrame;
	sf::Time frameTimer;
	const std::string animPrefix;
	const sf::Time frameTime;
	AnimationComponent(const sf::Vector2i& animRectSize, const std::string& prefix, sf::Time frameTime) :
		frameTime(frameTime) ,
		animPrefix(prefix)
	{
		this->animRectSize = animRectSize;
		frameTimer = sf::Time::Zero;
		AnimManager::InitAnimComponent(*this);
	}
};

#endif