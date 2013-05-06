
#ifndef __SOUNDMANAGER_H
#define __SOUNDMANAGER_H

#include <map>
#include <queue>
#include <list>
#include <memory>

#include "SFML/Audio.hpp"

class SoundManager
{
public:
	static std::shared_ptr<sf::Sound> PlaySound(const std::string& path, bool loop);
	static void PrecacheSound(const std::string& path);
private:
	
	static sf::SoundBuffer& GetSoundBuffer(const std::string& path);

	typedef std::map<std::string, sf::SoundBuffer>::iterator soundBufferIterator;
	static std::map<std::string, sf::SoundBuffer> soundBuffers;
	static std::list<std::shared_ptr<sf::Sound>> playingSounds;
};

#endif