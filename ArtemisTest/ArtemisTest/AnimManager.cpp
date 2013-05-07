
#include "AnimManager.h"

#include "AnimationComponent.h"

std::map<std::string, int> AnimManager::animMap;
std::vector<AnimManager::animInfo> AnimManager::animInfoVector;

void AnimManager::PlayAnim(AnimationComponent& animComponent, const std::string& animName)
{
	PlayAnim(animComponent, GetAnim(animComponent.animPrefix + animName));
}

void AnimManager::PlayAnim(AnimationComponent& animComponent)
{
	PlayAnim(animComponent, animComponent.curAnim);
}

void AnimManager::PlayAnim(AnimationComponent& animComponent, int anim)
{
	if(anim == -1 || animComponent.frameTimer > sf::Time::Zero) return;

	if(animComponent.curAnim == anim) {
		animComponent.curFrame++;
		if(animComponent.curFrame == animInfoVector[anim].end+1) {
			if(animInfoVector[anim].loop) {
				animComponent.curFrame = animInfoVector[anim].start;
			} else {
			PlayAnim(animComponent, "idle");
			}
		}
	} else {
		animComponent.curAnim = anim;
		animComponent.curFrame = animInfoVector[anim].start;
	}

	animComponent.frameTimer = animComponent.frameTime;
}

void AnimManager::InitAnimComponent(AnimationComponent& animComponent)
{
	AddAnim(animComponent, "idle", 0, 0, false);
	PlayAnim(animComponent, "idle");
}

int AnimManager::AddAnim(AnimationComponent& animComponent, const std::string& animName,
	int startFrame, int endFrame, bool animLoop)
{
	if(GetAnim(animComponent.animPrefix + animName) != -1) return -1;

	animMap[animComponent.animPrefix + animName] = animInfoVector.size();
	animInfoVector.push_back(animInfo());
	animInfoVector.back().start = startFrame;
	animInfoVector.back().end = endFrame;
	animInfoVector.back().loop = animLoop;

	return animInfoVector.size()-1;
}

int AnimManager::GetAnim(const std::string& anim)
{
	animMapIter findIter = animMap.find(anim);
	if(findIter != animMap.end()) {
		return findIter->second;
	} else {
		return -1;
	}
}