
#ifndef __ANIMMANAGER_H
#define __ANIMMANAGER_H

#include <map>
#include <vector>

class AnimationComponent;

class AnimManager
{
public:
	static void PlayAnim(AnimationComponent& animComponent, const std::string& animName);
	static void PlayAnim(AnimationComponent& animComponent);
	static int AddAnim(AnimationComponent& animComponent, const std::string& animName,
		int startFrame, int endFrame, bool animLoop);
	static void InitAnimComponent(AnimationComponent& animComponent);

private:
	struct animInfo {
		int start;
		int end;
		bool loop;
	};

	static void PlayAnim(AnimationComponent& animComponent, int anim);

	static int GetAnim(const std::string& anim);

	typedef std::map<std::string, int>::iterator animMapIter;
	static std::map<std::string, int> animMap;
	static std::vector<animInfo> animInfoVector;
};

#endif